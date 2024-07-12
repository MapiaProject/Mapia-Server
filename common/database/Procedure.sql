USE GameDB;

DELIMITER $$

DROP PROCEDURE IF EXISTS SP_GetUserByName $$
CREATE PROCEDURE SP_GetUserByName(
	IN nickname VARCHAR(32)
)
BEGIN
	SELECT clevel, exp FROM usercharacter uc WHERE uc.nickname = nickanme;
END $$

DROP PROCEDURE IF EXISTS SP_CreateUser $$
CREATE PROCEDURE SP_CreateUser(
	IN nickname VARCHAR(32)
)
BEGIN
	INSERT INTO usercharacter VALUES(nickname, 1, 0);
END $$

DROP PROCEDURE IF EXISTS SP_AddExp $$
CREATE PROCEDURE SP_AddExp(
	IN nickname VARCHAR(32),
    IN addExp INTEGER
)
BEGIN
	UPDATE UserCharacter SET exp = exp + addExp WHERE nickname = nickname;
END $$

DROP PROCEDURE IF EXISTS SP_LevelUp $$
CREATE PROCEDURE SP_LevelUp(
	IN nickname VARCHAR(32),
	IN curExp INTEGER
)
BEGIN
	UPDATE UserCharacter SET exp = curExp, clevel = clevel + 1 WHERE nickname = nickname;
END $$
DELIMITER ;

commit;