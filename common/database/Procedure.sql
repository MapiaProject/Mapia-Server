USE GameDB;

DELIMITER $$
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
	IN nickname VARCHAR(32)
)
BEGIN
	UPDATE UserCharacter SET exp = 0, clevel = clevel + 1 WHERE nickname = nickname;
END $$
DELIMITER ;

commit;