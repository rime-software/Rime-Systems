<?hh // strict

namespace Application\Models;

class ApiKey extends \ActiveRecord\Model
{
  static $belongs_to = [
    ['company', 'class_name' => '\\Application\\Models\\Company', 'readonly' => true]
  ];
}