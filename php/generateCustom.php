<?php

require('generateCustomFunc.php');

/*<?xml version="1.0" encoding="utf-8"?>
<feed xmlns="http://www.w3.org/2005/Atom">

<title>Fil d'exemple</title>
 <subtitle>Un titre secondaire.</subtitle>
 <link href="http://example.org/"/>
 <updated>2010-05-13T18:30:02Z</updated>
 <author>
   <name>Paul Martin</name>
   <email>paulmartin@example.com</email>
 </author>
 <id>urn:uuid:60a76c80-d399-11d9-b91C-0003939e0af6</id>

 <entry>
   <title>Des robots propulsés par Atom deviennent fous</title>
   <link href="http://example.org/2003/12/13/atom03"/>
   <id>urn:uuid:1225c695-cfb8-4ebb-aaaa-80da344efa6a</id>
   <updated>2010-04-01T18:30:02Z</updated>
   <summary>Poisson d'avril !</summary>
</entry>

   </feed>*/
//date("F d Y H:i:s.", filemtime($filename))
$feed = "<?xml version=\"1.0\" encoding=\"utf-8\"?>
<feed xmlns=\"http://www.w3.org/2005/Atom\">

       <title>Party Junkie</title>
 <subtitle>Un titre secondaire.</subtitle>
 <link href=\"https://doc0160.github.io/Party-Junkie/\"/>
 <updated>2010-05-13T18:30:02Z</updated>
 <author>
   <name>Tristan Magniez</name>
   <email>Tristan.Magniez@viacesi.fr</email>
 </author>
 <id>//TODO //PARTY //JUNKIE //RULES</id>

";
$nb = sizeof(scandir('../xml/'));
$name = scandir('../xml/');

function make_html_filename_from_xml_filename($t){
    return substr($t, 0, 3);
}
function make_title_from_xml_filename($t){
    return str_replace("_", " ", str_replace(".xml", "", $t));
}

for ($a = $nb -1; $a > 1; $a--) {
    $i = 0;
    $array = [];
    $f = file_get_contents('../xml/'.$name[$a]);
    
    EatWhiteSpace($i, $f);
    // GET RID OF <?xml ....
    while($f[$i] != "\n" && $i < strlen($f)){
        $i++;
    }
    // parse the full thing
    DoNode($i, $f, $array);
    //var_dump($array);

    $page = '
	<!DOCTYPE html>
	<html name="html">
	<head>
		<title>Blog Projet</title>
		<link rel="icon" type="image/png" href="../img/favicon.png" />

<link rel="alternate" type="application/atom+xml" title="Atom" href="../atom.xml" />

		<link rel="stylesheet" type="text/css" href="../css/style.css">
		<link rel="stylesheet" type="text/css" href="../css/code.css">

		<!-- js librairie -->
		<script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.0/jquery.min.js"></script>
		<script type="text/javascript" src="../js/script_menu.js"></script>
		<script src="https://cdn.rawgit.com/google/code-prettify/master/loader/run_prettify.js?skin=sunburst"></script>
	</head>
	<body name="body">

	<div id="menu">
		<ul>';
    $i =2;
    while ($i < $nb) {
		$temp = explode("-", $name[$i]);
	    $page .= '<li>'.
                 '<a href="'.make_html_filename_from_xml_filename($name[$i]).'">'.
				 '<span class="numbers">'.$temp[0]."</span>".
                 ' - '.
                 make_title_from_xml_filename($temp[1]).
                 '</a>'.
                 '</li>';
	    $i++;
    }
    
    $page .= '
</ul>

	<div id="menu_btn">
		<img class="btn" src="../img/menu.svg">
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
    for($j = 0; $j < sizeof($array["div"]["article"]); $j++)
	    $page .= "\n<article>\n".$array["div"]["article"][$j]."\n</article>\n";
    $page .= '
	</div>


<div id="sound_btn">
	<img src="../img/speaker.svg" id="svg_song" class="invisible">
	<img src="../img/mute.svg" id="svg_mute">
</div>

<script type="text/javascript" src="../js/script_song.js"></script>
</body>
</html>
';
	//$nameo = str_replace(".xml", ".html", $name[$a]);
    //echo $nameo."\n";
    //file_put_contents("../html/".$nameo, $page);
    echo make_html_filename_from_xml_filename($name[$a]).".html\n";
    file_put_contents("../html/".make_html_filename_from_xml_filename($name[$a]).".html", $page);
    $temp = explode("-", $name[$a]);
    $feed .= "<entry>
   <title>".$temp[0]." - ".make_title_from_xml_filename($temp[1])."</title>
   <link href=\"https://doc0160.github.io/Party-Junkie/html/".
             make_html_filename_from_xml_filename($name[$a]).".html\"/>
             <id>urn:uuid:1225c695-cfb8-4ebb-aaaa-80da344efa6a</id>
    <updated>".date("F d Y H:i:s.", filemtime("../xml/".$name[$a]))."</updated>
    <summary>//TODO //PARTY //JUNKIE //RULES //".filemtime("../xml/".$name[$a]))."</summary>
    </entry>

";
}
$feed .= "</feed>";
file_put_contents("../atom.xml", $feed);
echo "atom.xml";
?>
