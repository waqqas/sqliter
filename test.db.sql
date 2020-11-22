CREATE TABLE "app" (
	"id"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"state"	INTEGER NOT NULL,
	"data"	TEXT NOT NULL
);

INSERT INTO "main"."app" ("id", "state", "data") VALUES ('1', '0', "hello world");
INSERT INTO "main"."app" ("id", "state", "data") VALUES ('2', '1', "hi-there");
INSERT INTO "main"."app" ("id", "state", "data") VALUES ('3', '2', "1234");
