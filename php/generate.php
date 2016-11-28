<?php
$a = 2;
$nb = sizeof(scandir('../xml/'));
$name = scandir('../xml/');

while ($a < $nb) {
	# code...
$xml = new DomDocument();
$xml->load('../xml/'.$name[$a]);


$nb_article = $xml->getElementsByTagName("article")->length;

$page = '
	<!DOCTYPE html>
	<html name="html">
	<head>
		<title>Blog Projet</title>
		<link rel="icon" type="image/png" href="img/favicon.png" />


		<link rel="stylesheet" type="text/css" href="css/style.css">
		<link rel="stylesheet" type="text/css" href="css/code.css">

		<!-- js librairie -->
		<script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.0/jquery.min.js"></script>
		<script type="text/javascript" src="js/script_menu.js"></script>
		<script src="https://cdn.rawgit.com/google/code-prettify/master/loader/run_prettify.js?skin=sunburst"></script>
	</head>
	<body name="body">

	<div id="menu">
		<ul>';


$nb_xml = sizeof(scandir('../xml/'));
$name_xml = scandir('../xml/');

$i =2;
while ($i < $nb_xml) {
	# code...
	$page .= '<li><a href="'.str_replace(".xml", ".html", $name_xml[$i]).'">'.str_replace(".xml", "", $name_xml[$i]).'</a></li>';
	$i++;
}

$page .= '
</ul>

	<div id="menu_btn">
		<img class="btn" src="img/menu.svg">
	</div>
</div>
<div class="animation">
	<div class="mario"></div>
	<div class="cloud"></div>
	<div class="mountain1" id="mountain0"></div>
	<div class="mountain2" id="mountain1"></div>
	<div class="mountain1" id="mountain2"></div>
</div>
<div class="content" id="content">';

$j = 0;
while ($j < $nb_article) {
	# code...
	$page .= '<article>';
	$page .= '<h1>'.$xml->getElementsByTagName("h1")->item($j)->nodeValue.'</h1>';
	$page .= '<p>'.$xml->getElementsByTagName("p")->item($j)->nodeValue.'</p>';
	if (isset($xml->getElementsByTagName("pre")->item($j)->nodeValue)) {
		# code...
		$page .= '<div class="code" ><pre class="prettyprint lang-cpp">'.$xml->getElementsByTagName("pre")->item($j)->nodeValue.'</pre>';
	}
	$page .= '</article>';
	$j++;
}

$page .= '
	</div>


<div id="sound_btn">
	<img src="img/speaker.svg" id="svg_song" class="invisible">
	<img src="img/mute.svg" id="svg_mute">
</div>

<script type="text/javascript" src="js/script_song.js"></script>
</body>
</html>
';

file_put_contents("../".str_replace(".xml", ".html", $name[$a]), $page);

$a++;
}
?>