<?hh // strict

use \Rime\ActionDispatch\Dispatcher as Dispatcher;

$router = (new Dispatcher\Factory\RouterFactory)->newInstance();

$router->addGet('home','/')->addValues(
	array(
		'controller'=>'index',
		'action'=>'index',
		'template'=>'master',
		'format'=>'.html'
	)
);

$router->addGet('index.index','/index')->addValues(
	array(
		'controller'=>'index',
		'action'=>'index',
		'template'=>'master',
		'format'=>'.html'
	)
);