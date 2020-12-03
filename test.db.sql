CREATE TABLE "app" (
	"id"	INTEGER,
	"state"	INTEGER NOT NULL,
	"data"	TEXT,
	"float"	REAL,
	PRIMARY KEY("id" AUTOINCREMENT)
);
INSERT INTO "main"."app" ("id", "state") VALUES ('1', '0');
INSERT INTO "main"."app" ("id", "state") VALUES ('2', '1');
INSERT INTO "main"."app" ("id", "state") VALUES ('3', '2');
