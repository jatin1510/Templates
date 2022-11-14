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

-- 11. Make a function to find the current price of each game after deducting it's discount if available

-- Make a 

-- 11. List all the games which has never been updated
SELECT "Game_ID", "Game_Name"
FROM "Game"
WHERE "Last_Update" IS NULL;

-- 12. Find all the Player_IDs who have never reviewed any game
SELECT "Player_ID" 
FROM "Player" 
WHERE "Player_ID" NOT IN (SELECT DISTINCT "Player_ID"
					  	  FROM "Reviews");