DROP TABLE IF EXISTS `log`;


CREATE TABLE `log` (

  `id` int(11) NOT NULL AUTO_INCREMENT,

  `mac` varchar(255) utf8_unicode_ci,

  `time` timestamp DEFAULT NULL,

  `proccess` varchar(255) DEFAULT NULL,

  `message` longtext DEFAULT NULL,

  ) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;