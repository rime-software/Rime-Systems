<?hh // strict

namespace Application\Models;

class ApiKey extends \ActiveRecord\Model
{
  static $belongs_to = [
    ['company', 'class_name' => '\\Application\\Models\\Company', 'readonly' => true]
  ];
  
  public function validate_secret(?mixed $secret): bool
  {
    $crypt = BlowFish::crypt_salted_string($secret,$this->salt);
    return ($crypt == $this->secret) ? true : false;
  }
  
}