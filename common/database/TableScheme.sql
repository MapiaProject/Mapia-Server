USE GameDB;

CREATE TABLE UserCharacter(
	nickname varchar(32) NOT NULL PRIMARY KEY,
	clevel int NOT NULL,
);