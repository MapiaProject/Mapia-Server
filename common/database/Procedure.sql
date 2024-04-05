USE GameDB;

DELIMITER $$
DROP PROCEDURE IF EXISTS SP_GetAccounts;
CREATE PROCEDURE SP_GetAccounts(
)
BEGIN
	SELECT BIN_TO_UUID(uniqueId), nickname
	FROM AccountDB.UserAccount;
END $$
DELIMITER ;

commit;