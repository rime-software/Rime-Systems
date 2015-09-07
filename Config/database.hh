<?hh //strict
  
  require_once BASE_PATH.'/Rime/ActiveRecord/autoload.php';
  
  ActiveRecord\Config::initialize(function($cfg)
  {
    $cfg->set_model_directory(MODEL_PATH);
    $cfg->set_connections(array(
        'development' => 'mysql://rime:a007mxg999@192.168.1.113/rime_systems',
        'test' => 'mysql://root@localhost/rime_test',
      )
    );
  });
  
  $cfg = ActiveRecord\Config::instance();
  $cfg->set_default_connection(DEV_MODE ? 'development' : 'production');
  
  if(defined('RUN_TESTS'))
  {
    $cfg->set_default_connection('test');
  }