<?hh
  
$Database = ActiveRecord\ConnectionManager::get_connection()->connection;

$Database->query("
  CREATE TABLE IF NOT EXISTS `api_keys` (
    `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
    `company_id` int(11) unsigned NOT NULL,
    `key` varchar(64) NOT NULL DEFAULT '',
    `secret` varchar(64) NOT NULL DEFAULT '',
    `salt` varchar(34) NOT NULL DEFAULT '',
    `is_active` tinyint(1) NOT NULL DEFAULT '0',
    `ip_addr` varchar(15) NOT NULL DEFAULT '',
    `last_updated` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00' ON UPDATE CURRENT_TIMESTAMP,
    PRIMARY KEY (`id`)
  );
");

$Database->query("
  CREATE TABLE IF NOT EXISTS `companies` (
    `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
    `name` varchar(50) NOT NULL DEFAULT '',
    `addr_1` varchar(50) NOT NULL DEFAULT '',
    `addr_2` varchar(50) NOT NULL DEFAULT '',
    `city` varchar(35) NOT NULL,
    `state` varchar(2) NOT NULL,
    `zip` varchar(10) NOT NULL DEFAULT '',
    `phone` varchar(25) NOT NULL DEFAULT '',
    `website` varchar(75) DEFAULT '',
    PRIMARY KEY (`id`)
  );
");