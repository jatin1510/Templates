SET datestyle = euro;
SET SEARCH_PATH TO "video_game_db"

1. Employee

-- Table: video_game_db.Employee
 
-- DROP TABLE IF EXISTS video_game_db."Employee";
 
CREATE TABLE IF NOT EXISTS video_game_db."Employee"
(
   "Emp_ID" bigint NOT NULL,
   "F_Name" character varying COLLATE pg_catalog."default" NOT NULL,
   "L_Name" character varying COLLATE pg_catalog."default" NOT NULL,
   "Joining_Date" date NOT NULL,
   "Salary" bigint NOT NULL DEFAULT 0,
   CONSTRAINT "Employee_pkey" PRIMARY KEY ("Emp_ID")
)
 
TABLESPACE pg_default;
 
ALTER TABLE IF EXISTS video_game_db."Employee"
   OWNER to postgres;

2. Player

-- Table: video_game_db.Player
 
-- DROP TABLE IF EXISTS video_game_db."Player";
 
CREATE TABLE IF NOT EXISTS video_game_db."Player"
(
   "Player_ID" character varying COLLATE pg_catalog."default" NOT NULL,
   "Password" character varying COLLATE pg_catalog."default" NOT NULL,
   "F_Name" character varying COLLATE pg_catalog."default" NOT NULL,
   "L_Name" character varying COLLATE pg_catalog."default" NOT NULL,
   "DOB" date NOT NULL,
   "Email_ID" character varying COLLATE pg_catalog."default" NOT NULL,
   "Wallet" bigint NOT NULL DEFAULT 0,
   CONSTRAINT "Player_pkey" PRIMARY KEY ("Player_ID")
)
 
TABLESPACE pg_default;
 
ALTER TABLE IF EXISTS video_game_db."Player"
   OWNER to postgres;

3. Manager

-- Table: video_game_db.Manager
 
-- DROP TABLE IF EXISTS video_game_db."Manager";
 
CREATE TABLE IF NOT EXISTS video_game_db."Manager"
(
   "Manager_ID" bigint NOT NULL,
   "F_Name" character varying COLLATE pg_catalog."default" NOT NULL,
   "L_Name" character varying COLLATE pg_catalog."default" NOT NULL,
   CONSTRAINT "Manager_pkey" PRIMARY KEY ("Manager_ID")
)
 
TABLESPACE pg_default;
 
ALTER TABLE IF EXISTS video_game_db."Manager"
   OWNER to postgres;

4. Developer

-- Table: video_game_db.Developer
 
-- DROP TABLE IF EXISTS video_game_db."Developer";
 
CREATE TABLE IF NOT EXISTS video_game_db."Developer"
(
   "Dev_ID" bigint NOT NULL,
   "Name" character varying COLLATE pg_catalog."default" NOT NULL,
   CONSTRAINT "Developer_pkey" PRIMARY KEY ("Dev_ID")
)
 
TABLESPACE pg_default;
 
ALTER TABLE IF EXISTS video_game_db."Developer"
   OWNER to postgres;

5. Tags

-- Table: video_game_db.Tags
 
-- DROP TABLE IF EXISTS video_game_db."Tags";
 
CREATE TABLE IF NOT EXISTS video_game_db."Tags"
(
   "Tag_ID" bigint NOT NULL,
   "Tag_Name" character varying COLLATE pg_catalog."default" NOT NULL,
   CONSTRAINT "Tags_pkey" PRIMARY KEY ("Tag_ID")
)
 
TABLESPACE pg_default;
 
ALTER TABLE IF EXISTS video_game_db."Tags"
   OWNER to postgres;

6. Upcoming_Games

-- Table: video_game_db.Upcoming_Games
 
-- DROP TABLE IF EXISTS video_game_db."Upcoming_Games";
 
CREATE TABLE IF NOT EXISTS video_game_db."Upcoming_Games"
(
   "Game_ID" bigint NOT NULL,
   "Game_Name" character varying COLLATE pg_catalog."default" NOT NULL,
   "About" character varying COLLATE pg_catalog."default",
   "Release_Date" date NOT NULL,
   CONSTRAINT "Upcoming_Games_pkey" PRIMARY KEY ("Game_ID")
)
 
TABLESPACE pg_default;
 
ALTER TABLE IF EXISTS video_game_db."Upcoming_Games"
   OWNER to postgres;

7. Game

-- Table: video_game_db.Game
 
-- DROP TABLE IF EXISTS video_game_db."Game";
 
CREATE TABLE IF NOT EXISTS video_game_db."Game"
(
   "Game_ID" bigint NOT NULL,
   "Game_Name" character varying COLLATE pg_catalog."default" NOT NULL,
   "About" character varying COLLATE pg_catalog."default",
   "MRP" bigint NOT NULL DEFAULT 0,
   "Demo_Version" boolean NOT NULL,
   "Release_Date" date NOT NULL,
   "Last_Update" date,
   "Dev_ID" bigint NOT NULL,
   CONSTRAINT "Game_pkey" PRIMARY KEY ("Game_ID"),
   CONSTRAINT "Game" FOREIGN KEY ("Dev_ID")
       REFERENCES video_game_db."Developer" ("Dev_ID") MATCH SIMPLE
       ON UPDATE CASCADE
       ON DELETE CASCADE
)
 
TABLESPACE pg_default;
 
ALTER TABLE IF EXISTS video_game_db."Game"
   OWNER to postgres;

8. Achievements

-- Table: video_game_db.Achievements
 
-- DROP TABLE IF EXISTS video_game_db."Achievements";
 
CREATE TABLE IF NOT EXISTS video_game_db."Achievements"
(
   "Achv_ID" bigint NOT NULL,
   "Achv_Name" character varying COLLATE pg_catalog."default" NOT NULL,
   "Game_ID" bigint NOT NULL,
   CONSTRAINT "Achievements_pkey" PRIMARY KEY ("Achv_ID"),
   CONSTRAINT "FK_Game" FOREIGN KEY ("Game_ID")
       REFERENCES video_game_db."Game" ("Game_ID") MATCH SIMPLE
       ON UPDATE CASCADE
       ON DELETE CASCADE
)
 
TABLESPACE pg_default;
 
ALTER TABLE IF EXISTS video_game_db."Achievements"
   OWNER to postgres;

9. Achieves

-- Table: video_game_db.Achieves
 
-- DROP TABLE IF EXISTS video_game_db."Achieves";
 
CREATE TABLE IF NOT EXISTS video_game_db."Achieves"
(
   "Achv_ID" bigint NOT NULL,
   "Player_ID" character varying COLLATE pg_catalog."default" NOT NULL,
   "Date_Achieved" date NOT NULL,
   CONSTRAINT "Achieves_pkey" PRIMARY KEY ("Achv_ID", "Player_ID"),
   CONSTRAINT "FK_Achv" FOREIGN KEY ("Achv_ID")
       REFERENCES video_game_db."Achievements" ("Achv_ID") MATCH SIMPLE
       ON UPDATE CASCADE
       ON DELETE CASCADE,
   CONSTRAINT "FK_Player" FOREIGN KEY ("Player_ID")
       REFERENCES video_game_db."Player" ("Player_ID") MATCH SIMPLE
       ON UPDATE CASCADE
       ON DELETE CASCADE
)
 
TABLESPACE pg_default;
 
ALTER TABLE IF EXISTS video_game_db."Achieves"
   OWNER to postgres;

10. Belongs_To

-- Table: video_game_db.Belongs_To
 
-- DROP TABLE IF EXISTS video_game_db."Belongs_To";
 
CREATE TABLE IF NOT EXISTS video_game_db."Belongs_To"
(
   "Game_ID" bigint NOT NULL,
   "Tag_ID" bigint NOT NULL,
   CONSTRAINT "Belongs_To_pkey" PRIMARY KEY ("Game_ID", "Tag_ID"),
   CONSTRAINT "FK_Game" FOREIGN KEY ("Game_ID")
       REFERENCES video_game_db."Game" ("Game_ID") MATCH SIMPLE
       ON UPDATE CASCADE
       ON DELETE CASCADE,
   CONSTRAINT "FK_Tag" FOREIGN KEY ("Tag_ID")
       REFERENCES video_game_db."Tags" ("Tag_ID") MATCH SIMPLE
       ON UPDATE CASCADE
       ON DELETE CASCADE
)
 
TABLESPACE pg_default;
 
ALTER TABLE IF EXISTS video_game_db."Belongs_To"
   OWNER to postgres;

11. Discount

-- Table: video_game_db.Discount
 
-- DROP TABLE IF EXISTS video_game_db."Discount";
 
CREATE TABLE IF NOT EXISTS video_game_db."Discount"
(
   "Discount_ID" bigint NOT NULL,
   "Start_Date" date NOT NULL,
   "End_Date" date,
   "Percentage" double precision NOT NULL DEFAULT 0,
   "Emp_ID" bigint NOT NULL,
   "Game_ID" bigint NOT NULL,
   CONSTRAINT "Discount_pkey" PRIMARY KEY ("Discount_ID"),
   CONSTRAINT "FK_Employee" FOREIGN KEY ("Emp_ID")
       REFERENCES video_game_db."Employee" ("Emp_ID") MATCH SIMPLE
       ON UPDATE NO ACTION
       ON DELETE NO ACTION,
   CONSTRAINT "FK_Game" FOREIGN KEY ("Game_ID")
       REFERENCES video_game_db."Game" ("Game_ID") MATCH SIMPLE
       ON UPDATE CASCADE
       ON DELETE CASCADE,
   CONSTRAINT "CHK_Percentange" CHECK ("Percentage" >= 0::double precision AND "Percentage" <= 100::double precision) NOT VALID
)
 
TABLESPACE pg_default;
 
ALTER TABLE IF EXISTS video_game_db."Discount"
   OWNER to postgres;


12. Friendship

-- Table: video_game_db.Friendship
 
-- DROP TABLE IF EXISTS video_game_db."Friendship";
 
CREATE TABLE IF NOT EXISTS video_game_db."Friendship"
(
   "Initiator_ID" character varying COLLATE pg_catalog."default" NOT NULL,
   "Acceptor_ID" character varying COLLATE pg_catalog."default" NOT NULL,
   "Date_Friendship" date NOT NULL,
   CONSTRAINT "Friendship_pkey" PRIMARY KEY ("Initiator_ID", "Acceptor_ID"),
   CONSTRAINT "FK_Acceptor" FOREIGN KEY ("Acceptor_ID")
       REFERENCES video_game_db."Player" ("Player_ID") MATCH SIMPLE
       ON UPDATE CASCADE
       ON DELETE CASCADE,
   CONSTRAINT "FK_Initiator" FOREIGN KEY ("Initiator_ID")
       REFERENCES video_game_db."Player" ("Player_ID") MATCH SIMPLE
       ON UPDATE CASCADE
       ON DELETE CASCADE
)
 
TABLESPACE pg_default;
 
ALTER TABLE IF EXISTS video_game_db."Friendship"
   OWNER to postgres;

13. Payment_Card

-- Table: video_game_db.Payment_Card
 
-- DROP TABLE IF EXISTS video_game_db."Payment_Card";
 
CREATE TABLE IF NOT EXISTS video_game_db."Payment_Card"
(
   "Card_Number" bigint NOT NULL,
   "Card_Type" character varying COLLATE pg_catalog."default" NOT NULL,
   "Expiry_Date" date NOT NULL,
   "Player_ID" character varying COLLATE pg_catalog."default" NOT NULL,
   CONSTRAINT "Payment_Card_pkey" PRIMARY KEY ("Card_Number"),
   CONSTRAINT "Payment_Card" FOREIGN KEY ("Player_ID")
       REFERENCES video_game_db."Player" ("Player_ID") MATCH SIMPLE
       ON UPDATE CASCADE
       ON DELETE CASCADE
)
 
TABLESPACE pg_default;
 
ALTER TABLE IF EXISTS video_game_db."Payment_Card"
   OWNER to postgres;

14. Phone_No

-- Table: video_game_db.Phone_No
 
-- DROP TABLE IF EXISTS video_game_db."Phone_No";
 
CREATE TABLE IF NOT EXISTS video_game_db."Phone_No"
(
   "Player_ID" character varying COLLATE pg_catalog."default" NOT NULL,
   "Ph_No" bigint NOT NULL,
   CONSTRAINT "Phone_No_pkey" PRIMARY KEY ("Player_ID", "Ph_No"),
   CONSTRAINT "FK_Player" FOREIGN KEY ("Player_ID")
       REFERENCES video_game_db."Player" ("Player_ID") MATCH SIMPLE
       ON UPDATE CASCADE
       ON DELETE CASCADE
)
 
TABLESPACE pg_default;
 
ALTER TABLE IF EXISTS video_game_db."Phone_No"
   OWNER to postgres;

15. Pre_Registers

-- Table: video_game_db.Pre_Registers
 
-- DROP TABLE IF EXISTS video_game_db."Pre_Registers";
 
CREATE TABLE IF NOT EXISTS video_game_db."Pre_Registers"
(
   "Player_ID" character varying COLLATE pg_catalog."default" NOT NULL,
   "Game_ID" bigint NOT NULL,
   "Date_Registered" date NOT NULL,
   CONSTRAINT "Pre_Registers_pkey" PRIMARY KEY ("Game_ID", "Player_ID"),
   CONSTRAINT "FK_Game" FOREIGN KEY ("Game_ID")
       REFERENCES video_game_db."Upcoming_Games" ("Game_ID") MATCH SIMPLE
       ON UPDATE CASCADE
       ON DELETE CASCADE,
   CONSTRAINT "FK_Player" FOREIGN KEY ("Player_ID")
       REFERENCES video_game_db."Player" ("Player_ID") MATCH SIMPLE
       ON UPDATE CASCADE
       ON DELETE CASCADE
)
 
TABLESPACE pg_default;
 
ALTER TABLE IF EXISTS video_game_db."Pre_Registers"
   OWNER to postgres;

16. Purchase*

-- Table: video_game_db.Purchase
 
-- DROP TABLE IF EXISTS video_game_db."Purchase";
 
CREATE TABLE IF NOT EXISTS video_game_db."Purchase"
(
   "Purchase_ID" character varying NOT NULL,
   "Purchase_Type" character varying COLLATE pg_catalog."default" NOT NULL,
   "Game_ID" bigint NOT NULL,
   "Player_ID" character varying COLLATE pg_catalog."default" NOT NULL,
   "Date_Purchased" timestamp without time zone NOT NULL,
   "Card_Number" bigint,
   CONSTRAINT "Purchase_pkey" PRIMARY KEY ("Purchase_ID"),
   CONSTRAINT "FK_Game" FOREIGN KEY ("Game_ID")
       REFERENCES video_game_db."Game" ("Game_ID") MATCH SIMPLE
       ON UPDATE NO ACTION
       ON DELETE NO ACTION,
   CONSTRAINT "FK_Player" FOREIGN KEY ("Player_ID")
       REFERENCES video_game_db."Player" ("Player_ID") MATCH SIMPLE
       ON UPDATE NO ACTION
       ON DELETE NO ACTION
)
 
TABLESPACE pg_default;
 
ALTER TABLE IF EXISTS video_game_db."Purchase"
   OWNER to postgres;

17. Reviews

-- Table: video_game_db.Reviews
 
-- DROP TABLE IF EXISTS video_game_db."Reviews";
 
CREATE TABLE IF NOT EXISTS video_game_db."Reviews"
(
   "Player_ID" character varying COLLATE pg_catalog."default" NOT NULL,
   "Game_ID" bigint NOT NULL,
   "Rate" integer NOT NULL,
   "Feedback" character varying COLLATE pg_catalog."default",
   CONSTRAINT "Reviews_pkey" PRIMARY KEY ("Player_ID", "Game_ID"),
   CONSTRAINT "FK_Game" FOREIGN KEY ("Game_ID")
       REFERENCES video_game_db."Game" ("Game_ID") MATCH SIMPLE
       ON UPDATE CASCADE
       ON DELETE CASCADE,
   CONSTRAINT "FK_Player" FOREIGN KEY ("Player_ID")
       REFERENCES video_game_db."Player" ("Player_ID") MATCH SIMPLE
       ON UPDATE CASCADE
       ON DELETE CASCADE,
   CONSTRAINT "CHK_Rate" CHECK ("Rate" >= 1 AND "Rate" <= 5) NOT VALID
)
 
TABLESPACE pg_default;
 
ALTER TABLE IF EXISTS video_game_db."Reviews"
   OWNER to postgres;

18. Season_Rewards

-- Table: video_game_db.Season_Rewards
 
-- DROP TABLE IF EXISTS video_game_db."Season_Rewards";
 
CREATE TABLE IF NOT EXISTS video_game_db."Season_Rewards"
(
   "Season_No" bigint NOT NULL,
   "Reward_Amount" bigint NOT NULL,
   "Game_ID" bigint NOT NULL,
   "Player_ID" character varying COLLATE pg_catalog."default" NOT NULL,
   "Emp_ID" bigint NOT NULL,
   "Date_Rewarded" date NOT NULL,
   CONSTRAINT "Season_Rewards_pkey" PRIMARY KEY ("Season_No", "Game_ID"),
   CONSTRAINT "FK_Emp" FOREIGN KEY ("Emp_ID")
       REFERENCES video_game_db."Employee" ("Emp_ID") MATCH SIMPLE
       ON UPDATE NO ACTION
       ON DELETE NO ACTION,
   CONSTRAINT "FK_Game" FOREIGN KEY ("Game_ID")
       REFERENCES video_game_db."Game" ("Game_ID") MATCH SIMPLE
       ON UPDATE NO ACTION
       ON DELETE NO ACTION,
   CONSTRAINT "FK_Player" FOREIGN KEY ("Player_ID")
       REFERENCES video_game_db."Player" ("Player_ID") MATCH SIMPLE
       ON UPDATE NO ACTION
       ON DELETE NO ACTION
)
 
TABLESPACE pg_default;
 
ALTER TABLE IF EXISTS video_game_db."Season_Rewards"
   OWNER to postgres;

19. Systems_Supported

-- Table: video_game_db.Systems_Supported
 
-- DROP TABLE IF EXISTS video_game_db."Systems_Supported";
 
CREATE TABLE IF NOT EXISTS video_game_db."Systems_Supported"
(
   "Game_ID" bigint NOT NULL,
   "System_Name" character varying COLLATE pg_catalog."default" NOT NULL,
   CONSTRAINT "Systems_Supported_pkey" PRIMARY KEY ("Game_ID", "System_Name"),
   CONSTRAINT "FK_Game" FOREIGN KEY ("Game_ID")
       REFERENCES video_game_db."Game" ("Game_ID") MATCH SIMPLE
       ON UPDATE CASCADE
       ON DELETE CASCADE
)
 
TABLESPACE pg_default;
 
ALTER TABLE IF EXISTS video_game_db."Systems_Supported"
   OWNER to postgres;

20. Tournament

-- Table: video_game_db.Tournament
 
-- DROP TABLE IF EXISTS video_game_db."Tournament";
 
CREATE TABLE IF NOT EXISTS video_game_db."Tournament"
(
   "Tournament_ID" bigint NOT NULL,
   "Tournament_Name" character varying COLLATE pg_catalog."default" NOT NULL,
   "Start_Date" date NOT NULL,
   "End_Date" date,
   "Game_ID" bigint NOT NULL,
   CONSTRAINT "Tournament_pkey" PRIMARY KEY ("Tournament_ID"),
   CONSTRAINT "FK_Game" FOREIGN KEY ("Game_ID")
       REFERENCES video_game_db."Game" ("Game_ID") MATCH SIMPLE
       ON UPDATE CASCADE
       ON DELETE CASCADE
)
 
TABLESPACE pg_default;
 
ALTER TABLE IF EXISTS video_game_db."Tournament"
   OWNER to postgres;


COPY "video_game_db"."Employee" FROM '/private/tmp/CSVs/Employee.csv' DELIMITER ',' NULL AS 'null' csv header;
SELECT * FROM "video_game_db"."Employee";

COPY "video_game_db"."Player" FROM '/private/tmp/CSVs/Player.csv' DELIMITER ',' NULL AS 'null' csv header;
SELECT * FROM "video_game_db"."Player";

COPY "video_game_db"."Manager" FROM '/private/tmp/CSVs/Manager.csv' DELIMITER ',' NULL AS 'null' csv header;
SELECT * FROM "video_game_db"."Manager";

COPY "video_game_db"."Developer" FROM '/private/tmp/CSVs/Developer.csv' DELIMITER ',' NULL AS 'null' csv header;
SELECT * FROM "video_game_db"."Developer";

COPY "video_game_db"."Tags" FROM '/private/tmp/CSVs/Tags.csv' DELIMITER ',' NULL AS 'null' csv header;
SELECT * FROM "video_game_db"."Tags";

COPY "video_game_db"."Upcoming_Games" FROM '/private/tmp/CSVs/Upcoming_Games.csv' DELIMITER ',' NULL AS 'null' csv header;
SELECT * FROM "video_game_db"."Upcoming_Games";

COPY "video_game_db"."Game" FROM '/private/tmp/CSVs/Game.csv' DELIMITER ',' NULL AS 'null' csv header;
SELECT * FROM "video_game_db"."Game";

COPY "video_game_db"."Achievements" FROM '/private/tmp/CSVs/Achievements.csv' DELIMITER ',' NULL AS 'null' csv header;
SELECT * FROM "video_game_db"."Achievements";

COPY "video_game_db"."Achieves" FROM '/private/tmp/CSVs/Achieves.csv' DELIMITER ',' NULL AS 'null' csv header;
SELECT * FROM "video_game_db"."Achieves";

COPY "video_game_db"."Belongs_To" FROM '/private/tmp/CSVs/Belongs_To.csv' DELIMITER ',' NULL AS 'null' csv header;
SELECT * FROM "video_game_db"."Belongs_To";

COPY "video_game_db"."Discount" FROM '/private/tmp/CSVs/Discount.csv' DELIMITER ',' NULL AS 'null' csv header;
SELECT * FROM "video_game_db"."Discount";

COPY "video_game_db"."Friendship" FROM '/private/tmp/CSVs/Friendship.csv' DELIMITER ',' NULL AS 'null' csv header;
SELECT * FROM "video_game_db"."Friendship";

COPY "video_game_db"."Payment_Card" FROM '/private/tmp/CSVs/Payment_Card.csv' DELIMITER ',' NULL AS 'null' csv header;
SELECT * FROM "video_game_db"."Payment_Card";

COPY "video_game_db"."Phone_No" FROM '/private/tmp/CSVs/Phone_No.csv' DELIMITER ',' NULL AS 'null' csv header;
SELECT * FROM "video_game_db"."Phone_No";

COPY "video_game_db"."Pre_Registers" FROM '/private/tmp/CSVs/Pre_Registers.csv' DELIMITER ',' NULL AS 'null' csv header;
SELECT * FROM "video_game_db"."Pre_Registers";

COPY "video_game_db"."Purchase" FROM '/private/tmp/CSVs/Purchase.csv' DELIMITER ',' NULL AS 'null' csv header;
SELECT * FROM "video_game_db"."Purchase";

COPY "video_game_db"."Reviews" FROM '/private/tmp/CSVs/Reviews.csv' DELIMITER ',' NULL AS 'null' csv header;
SELECT * FROM "video_game_db"."Reviews";

COPY "video_game_db"."Season_Rewards" FROM '/private/tmp/CSVs/Season_Rewards.csv' DELIMITER ',' NULL AS 'null' csv header;
SELECT * FROM "video_game_db"."Season_Rewards";

COPY "video_game_db"."Systems_Supported" FROM '/private/tmp/CSVs/Systems_Supported.csv' DELIMITER ',' NULL AS 'null' csv header;
SELECT * FROM "video_game_db"."Systems_Supported";

COPY "video_game_db"."Tournament" FROM '/private/tmp/CSVs/Tournament.csv' DELIMITER ',' NULL AS 'null' csv header;
SELECT * FROM "video_game_db"."Tournament";