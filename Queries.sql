-- 1. Find the count of all the games which can be played on each of the systems available
SELECT "System_Name", COUNT("Game_ID")
FROM "Systems_Supported"
GROUP BY "System_Name";

-- 2. Select and sort the Game_IDs in decreasing order of their average ratings
SELECT "Game_ID", AVG("Rate") as avg
FROM "Reviews"
GROUP BY "Game_ID"
ORDER BY avg DESC;

-- 3. List all the rewards set by the employee having the maximum salary
SELECT * 
FROM "Season_Rewards"
WHERE "Emp_ID" = (SELECT "Emp_ID"
				  FROM "Employee"
				  WHERE "Salary" = (SELECT MAX("Salary")
				 				    FROM "Employee"));

-- 4. Count the number of purchases made for each purchase type, in last 5 years (2018 - 2022)
SELECT "Purchase_Type", COUNT("Purchase_ID")
FROM "Purchase"
WHERE EXTRACT('year' from "Date_Purchased") >= 2018 AND EXTRACT('year' from "Date_Purchased") <= 2022
GROUP BY "Purchase_Type";

-- 5. List the names of all the players with the count of the total phone numbers each of them have
SELECT "Player_ID", "F_Name", COUNT("Ph_No")
FROM "Player" NATURAL JOIN "Phone_No"
GROUP BY "Player_ID", "F_Name";

-- 6. List the details of each game having the demo version and is not free of cost
SELECT *
FROM "Game"
WHERE "Demo_Version" = TRUE AND "MRP" != 0;

-- 7. Find 5 tags belonging to maximum number of games.
SELECT "Tag_ID", COUNT("Tag_ID") as CNT
FROM "Belongs_To"
GROUP BY "Tag_ID"
ORDER BY CNT DESC
LIMIT 5;

-- 8. Select all the Game_IDs and their corresponding Discount_IDs, having discount percentage greater than 40.
SELECT "Discount_ID", "Game_ID", "Percentage"
FROM "Discount"
WHERE "Percentage" > 40; 

-- 9. List down all the game names and respective Discount which will be available for discount offer on 14 Feb 2023.
SELECT "Game_ID", "Game_Name", "Percentage"
FROM "Discount" NATURAL JOIN "Game"
WHERE ("Start_Date", "End_Date") OVERLAPS (DATE '2023-02-14', DATE '2023-02-14');

-- 10. Sort the tournaments in increasing order of their time duration.
SELECT "Tournament_ID", AGE("End_Date", "Start_Date") as Tournament_Duration
FROM "Tournament"
ORDER BY Tournament_Duration DESC;

-- 11. List all the games which has never been updated
SELECT "Game_ID", "Game_Name"
FROM "Game"
WHERE "Last_Update" IS NULL;

-- 12. Find all the Player_IDs who have never reviewed any game
SELECT "Player_ID" 
FROM "Player" 
WHERE "Player_ID" NOT IN (SELECT DISTINCT "Player_ID"
					  	  FROM "Reviews");

-- 13. Using a function, find the current price of each game after deducting it's discount if available
CREATE OR REPLACE function "video_game_db".FinalPrice(G_ID bigint)
RETURNS double precision
LANGUAGE 'plpgsql'
AS $BODY$
DECLARE disc double precision;
DECLARE price double precision;
DECLARE mrp bigint;
BEGIN
		disc := 0;
		price := 0;
		mrp := (SELECT "MRP"
			    FROM "Game"
			    WHERE "Game"."Game_ID" = G_ID);
					 
		IF(G_ID IN (SELECT "Game_ID" FROM "Discount")) THEN
			disc := (SELECT "Percentage"
			     	 FROM "Discount"
			     	 WHERE "Discount"."Game_ID" = G_ID);
					 
			IF(mrp = 0) THEN
				price := 0;
			ELSE
				price := mrp - ((mrp * disc) / 100.00);
			END IF;
		ELSE
			price := mrp;
		END IF;
		
	RETURN price;
END;
$BODY$;

SELECT "Game_ID", video_game_db.FinalPrice("Game_ID")
FROM "Game";

-- 14. Trigger
CREATE OR REPLACE function "video_game_db".validate_purchase_before()

RETURNS TRIGGER
LANGUAGE 'plpgsql'
AS $BODY$
DECLARE W double precision;
DECLARE Game_Price double precision;

BEGIN
	IF(NEW."Purchase_Type" != 'Wallet') THEN
		RETURN NEW;
	END IF;
	
	SELECT video_game_db.FinalPrice("Game_ID") INTO Game_Price
	FROM "Game"
	WHERE "Game_ID" = NEW."Game_ID";
		
	SELECT "Wallet" INTO W
	FROM "Player"
	WHERE "Player_ID" = NEW."Player_ID";
	
	IF(W >= Game_Price) THEN
		RAISE NOTICE 'Purchase Successfull';
		RETURN NEW;
	ELSE
		RAISE NOTICE 'Not Enough Balance in Wallet';
	END IF;
END;
$BODY$;

CREATE OR REPLACE TRIGGER Trig1
BEFORE INSERT
ON "video_game_db"."Purchase"
FOR EACH ROW
EXECUTE PROCEDURE "video_game_db".validate_purchase_before();