<?hh // strict

namespace Application\Models;

class BlowFish
{
	public static function generate_salt($type="salt")
	{
		$string = $type.'B10wF1$h3nCrYpTr1m3';
		$string .= strtotime(date('Y-m-d'));
		
		return crypt($string,self::random_hash());	
	}

	public static function crypt_salted_string($password,$salt)
	{
		return crypt($password, '$2a$07$'.$salt);
	}
	
	public static function random_hash()
	{
		return bin2hex(mcrypt_create_iv(32, MCRYPT_DEV_URANDOM));
	}

}