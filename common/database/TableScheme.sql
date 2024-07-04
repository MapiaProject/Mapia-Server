USE GameDB;

CREATE TABLE UserCharacter(
	nickname varchar(32) NOT NULL PRIMARY KEY,
	clevel INT NOT NULL,
	exp INT NOT NULL
);