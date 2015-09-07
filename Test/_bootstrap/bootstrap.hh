<?hh // strict
  
  //----------
  // Set framework configurations to a unit-test configuration
  define('RUN_TESTS',true);
  
  //----------
  // Load framework configurations
  require_once 'Config/config.hh';
  require_once 'migrations.hh';
  
  echo "\n Debug: ".getcwd()."\n";
  
  //----------
  // Make some Rime configs global
  $Rime = \Rime\System\Framework\Rime::getInstance();    
  $Rime->attach( new \Rime\System\Framework\Loader(),'load');
  $Rime->attach( new \Rime\ActionDispatch\Session\Factory\SessionFactory,'sessionFactory');
  
  