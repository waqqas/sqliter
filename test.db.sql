CREATE TABLE "app" (
	"id"	INTEGER,
	"state"	INTEGER NOT NULL,
	"data"	TEXT NOT NULL,
	"float"	REAL NOT NULL DEFAULT 0.0,
	PRIMARY KEY("id" AUTOINCREMENT)
);
INSERT INTO "main"."app" ("id", "state", "data", "float") VALUES ('1', '0', "hello world", 0.1);
INSERT INTO "main"."app" ("id", "state", "data", "float") VALUES ('2', '1', "hi-there", 0.2);
INSERT INTO "main"."app" ("id", "state", "data", "float") VALUES ('3', '2', "1234", 3.1415926);
