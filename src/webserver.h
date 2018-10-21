#define STATIC_PAGE_HOME "<!DOCTYPE html><html lang=\"en\"><head>	<script>		function onload() {			var xhr = new XMLHttpRequest();			xhr.open(\"GET\", \"/api/config\");			xhr.addEventListener(\"readystatechange\", function () {				if (this.readyState === this.DONE) {					var d = JSON.parse(this.responseText);					if (!d) {						return;					}					document.getElementById(\"rangeR\").value = d.color.r;					document.getElementById(\"rangeG\").value = d.color.g;					document.getElementById(\"rangeB\").value = d.color.b;					document.getElementById(\"chkAutoChange\").checked = d.autoupdate.enabled;					document.getElementById(\"chkIsLightOn\").checked = d.isLightOn;					document.getElementById(\"inputRange\").value = d.autoupdate.interval;					document.getElementById(\"rangeBrightness\").value = d.brightness;				}			});			xhr.send();		}		function msToTime(duration) {			var seconds = parseInt((duration / 1000) % 60), minutes = parseInt((duration / (1000 * 60)) % 60);			minutes = (minutes < 10) ? \"0\" + minutes : minutes;			seconds = (seconds < 10) ? \"0\" + seconds : seconds;			return minutes + \":\" + seconds;		}		function sendConfig() {			var autoupdate = {};			var r = document.getElementById(\"rangeR\").value;			var g = document.getElementById(\"rangeG\").value;			var b = document.getElementById(\"rangeB\").value;			var brightness = document.getElementById(\"rangeBrightness\").value;			var isLightOn = document.getElementById(\"chkIsLightOn\").checked ? 1 : 0;			autoupdate.enabled = document.getElementById(\"chkAutoChange\").checked ? 1 : 0;			autoupdate.interval = document.getElementById(\"inputRange\").value;			var j = JSON.stringify({\"isLightOn\": isLightOn,  \"color\": { \"r\": r, \"g\": g, \"b\": b }, \"autoupdate\": autoupdate, \"brightness\" : brightness });			var xhr = new XMLHttpRequest();			xhr.open(\"POST\", \"/api/config\");			xhr.setRequestHeader(\"Content-Type\", \"application/json;charset=UTF-8\");			xhr.send(j);		}	</script>	<meta name=\"apple-mobile-web-app-capable\" content=\"yes\">	<title>Roy Light</title>	<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">	<style>		body {	margin: 0;	padding: 0;}.divSection {	text-align: center;	width: 80%;	padding-left: 10%;	padding-right: 10%;	margin-top: 10px;	margin-bottom: 10px;	border: 2px green;}input[type=range] {	-webkit-appearance: none;	width: 100%;	height: 40px;	margin-bottom: 14px;	margin-top: 14px;}</style></head><body onload=\"onload()\">	<h1 style=\"text-align: center\">Roy Light</h1>	<div class=\"divSection\" id=\"divRange\">		<input type=\"range\" name=\"volume\" min=\"0\" max=\"255\" id=\"rangeR\" style=\"background-color: red\" onChange=\"sendConfig()\" />		<input type=\"range\" name=\"volume\" min=\"0\" max=\"255\" id=\"rangeG\" style=\"background-color: green\" onChange=\"sendConfig()\" />		<input type=\"range\" name=\"volume\" min=\"0\" max=\"255\" id=\"rangeB\" style=\"background-color: blue\" onChange=\"sendConfig()\" />		<input type=\"range\" name=\"volume\" min=\"0\" max=\"100\" id=\"rangeBrightness\" style=\"background-color:gray\" onChange=\"sendConfig()\" />	</div>	<div class=\"divSection\" id=\"divAutoControl\" style=\"text-align: left\">		<input type=\"checkbox\" id=\"chkIsLightOn\" onchange=\"sendConfig()\">		<span>Light on?</span><br>		<input type=\"checkbox\" id=\"chkAutoChange\" onchange=\"sendConfig()\">		<span>Change color automatically</span><br> <span>Interval			(seconds): <input type=\"text\" value=\"60\" onChange=\"sendConfig()\" id=\"inputRange\" pattern=\"\\d*\">		</span>	</div></body></html>"
void setupWebServer();
void loopWebServer();
