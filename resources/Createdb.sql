CREATE TABLE `register` (

  `mac` varchar(255) utf8_unicode_ci,

  `os` varchar(255) DEFAULT NULL,

  `antivirus` varchar(255) DEFAULT NULL,

);

CREATE TABLE `log` (

  `id` int(11) NOT NULL AUTO_INCREMENT,

  `mac` varchar(255) utf8_unicode_ci,

  `time` timestamp DEFAULT NULL,

  `process` varchar(255) DEFAULT NULL,

  `message` longtext DEFAULT NULL,

  );