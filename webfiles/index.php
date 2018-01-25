<!DOCTYPE HTML>
<html>
<head>
	<title>SnowMeter</title>
	<script src="http://ajax.googleapis.com/ajax/libs/jquery/1.3.2/jquery.min.js" type="text/javascript" charset="utf-8"></script>
	<link href="/css/bootstrap.css" rel="stylesheet" type="text/css">
	<link href="/css/bootstrap-theme.css" rel="stylesheet" type="text/css">
	<link href="/css/bootstrap.min.css" rel="stylesheet" type="text/css">
	<link rel="stylesheet" type="text/css" href="main.css">
	<script src="/js/bootstrap.min.js"></script>
	<script src="/js/bootstrap.js"></script>
	<script src="/js/jquery.backstretch.min.js"></script>
</head>
<body>
    <script type="text/javascript">
	
      window.setInterval(function() {

        var deviceID = "REDACTED";
        var accessToken = "REDACTED
        var race = "racewax";
        var snow = "snowtype";
        var train = "trainingwax";
        var tempf = "temp";
		
        requestURL = "https://api.spark.io/v1/devices/" + deviceID + "/" + tempf + "/?access_token=" + accessToken;
        $.getJSON(requestURL, function(json) {
            document.getElementById("temp").innerHTML = json.result;
        });
		
		requestURL = "https://api.spark.io/v1/devices/" + deviceID + "/" + snow + "/?access_token=" + accessToken;
        $.getJSON(requestURL, function(json) {
            document.getElementById("snow").innerHTML = json.result;
        });
		
		requestURL = "https://api.spark.io/v1/devices/" + deviceID + "/" + race + "/?access_token=" + accessToken;
        $.getJSON(requestURL, function(json) {
            document.getElementById("race").innerHTML = json.result;
        });
		
		requestURL = "https://api.spark.io/v1/devices/" + deviceID + "/" + train + "/?access_token=" + accessToken;
        $.getJSON(requestURL, function(json) {
            document.getElementById("training").innerHTML = json.result;
        });
		
    }, 5000);
    </script>
	<div id="header">
		<h2>Wax Recomendation</h2>
			<p>Questioning your wax choice? Let us help you out.</p>
		</h2>
	</div>
	<div id="package">
		<div id="holder">
			<div class="row">
				<div class="col-md-3">
					<h3>Snow Temperature</h3>
					<span id="one">
						<span id="temp">Waiting for data...</span>
					</span>
				</div>
				<div class="col-md-3">
					<h3>Snow Type</h3>
					<span id="two">
						<span id="snow">Waiting for data...</span>
					</span>
				</div>
				<div class="col-md-3">
					<h3>Racing Wax</h3>
					<span id="three">
						<span id="race">Waiting for data...</span>
					</span>
				</div>
				<div class="col-md-3">
					<h3>Training Wax</h3>
					<span id ="four">
						<span id="training">Waiting for data...</span>
					</span>
				</div>
			</div>
		</div>
	</div>
	
	<div id="footer">
		<p> &copy; <?php auto_copyright('2015') ?> Peter Irvine, Madeline Arpin, and Sean Rogers</p>
	</div>
	
	
   
    
<?php
		function auto_copyright($year = 'auto'){
			if(intval($year) == 'auto'){ $year = date('Y'); } 
			if(intval($year) == date('Y')){ echo intval($year); }
			if(intval($year) < date('Y')){ echo intval($year) . ' - ' . date('Y'); }
			if(intval($year) > date('Y')){ echo date('Y'); }
		}
	?>
	
	
</body>
</html>

