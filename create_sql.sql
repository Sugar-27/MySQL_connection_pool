CREATE database chat;

USE database chat;

CREATE TABLE IF NOT EXISTS `user`(
   `id` INT(11) UNSIGNED AUTO_INCREMENT,
   `name` VARCHAR(50) DEFAULT NULL,
   `age` INT(11) DEFAULT NULL,
   `sex` ENUM('male', 'female'),
   PRIMARY KEY ( `id` )
)ENGINE=InnoDB DEFAULT CHARSET=utf8;