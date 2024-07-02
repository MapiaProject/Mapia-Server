USE GAMEDB;

CREATE TABLE `usercharacter`(
	`nickname` varchar(32) NOT NULL,
	`clevel` int NOT NULL,
	PRIMARY KEY (`nickname`)
);