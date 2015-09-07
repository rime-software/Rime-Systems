
<script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.4/jquery.min.js"></script>
<section>
  <pre id="response">
    
  </pre>
</section>

<section>
  <p>
    <label>
      API Key:  
      <input id="js-apikey" width="250" />
    </label>
    <br>
    <label>
      Secret:  
      <input id="js-secret" width="250" />
    </label>    
  </p>
  <p>
    <label>
      Session ID: 
      <input id="js-sessid" width="250" />
    </label>
  </p>
  <p>
    <label>
      URL: 
      <input id="js-url" width="250" />
    </label>
  </p>
</section>

<section>
  <p>
    <button id="js-login">Login</button>
    <button id="js-get">GET</button>
    <button id="js-post">POST</button>
  </p>
</section>

<script>

$(document).ready(function(){
  
  $('#js-login').on('click',function(){
    data = {};
    data.key = $('#js-apikey').val();
    data.secret = $('#js-secret').val();
    
    $.post('/api/v1/login', data, function(response){
      $('#response').html(JSON.stringify(response, null, 2));
    });
    
  });
  
  $('#js-get').on('click',function(){
    api_get({});
  });
  
  $('#js-post').on('click',function(){
    api_post({});
  });
  
});

function generate_url()
{
  url = '/api/v1/';
  url += $('#js-url').val();
  return url;
}

function api_post( data )
{
  url = generate_url();
  $.post(url, data, function(response){
    $('#response').html(JSON.stringify(response, null, 2));
  });
  
}

function api_get( data )
{
  url = generate_url();
  $.get(url, data, function(response){
    $('#response').html(JSON.stringify(response, null, 2));
  });
}
</script>