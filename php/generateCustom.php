<?php

function EatWhiteSpace(&$i, $string){
    while(strlen($string) > $i &&
          ($string[$i] == ' ' ||
          $string[$i] == "\t" ||
          $string[$i] == "\r" ||
          $string[$i] == "\n")){
        $i++;
    }
}

function ReadTag(&$i, $string){
    $out = '';
    EatWhiteSpace($i, $string);
    if($string[$i] == '<'){
        $i++;
        while($string[$i] != '>') {
            $out .= $string[$i];
            $i++;
        }
        $i++;
        return $out;
    }
}

function ReadText(&$i, $string){
   $text = "";
    while(($string[$i] != '>' &&
           $string[$i] != '<') &&
          strlen($string) > $i){
        $text .= $string[$i];
        $i++;
    }
    return $text;
}

function ReadFullText(&$i, $string){
    $text = "";
    while(strlen($string) > $i){
        if($string[$i] == '<'){
            $tag = ReadTag($i, $string);
            if($tag == "/article"){
                return $text;
            }else{
                $text .= '<'.$tag.'>';
            }
        }
        $text .= $string[$i];
        $i++;
    }
    return $text;
}

function DoNode(&$i, $f, &$array) {
    while($i < strlen($f)){
        EatWhiteSpace($i, $f);
        if(strlen($f)<=$i){
            break;
        }
        if($f[$i] == '<') {
            $tag = ReadTag($i, $f);
            if($tag[0] == "/"){
                return;
            }else{
                if($tag != "article"){
                    DoNode($i, $f, $array[$tag]);
                }else{
                    $text = ReadFullText($i, $f);
                    $array[$tag][] = trim($text);
                }
            }
        }else{
            $text = ReadText($i, $f);
            $array[] = $text;
        }
    }
}

$a = 2;

$nb = sizeof(scandir('../xml/'));
$name = scandir('../xml/');

while ($a < $nb) {
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
	    $page .= '<li><a href="'.
                 str_replace(".xml", ".html", $name[$i]).'">'.
				 '<span class="numbers">'.$temp[0]."</span>".
                  ' - '.str_replace("_", " ", str_replace(".xml", "", $temp[1])).'</a></li>';
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

    $j = 0;
    while ($j < sizeof($array["div"]["article"])) {
	    # code...
	    $page .= "\n<article>\n".$array["div"]["article"][$j]."\n</article>\n";
	    $j++;
    }

    $page .= '
	</div>


<div id="sound_btn">
	<img src="../img/speaker.svg" id="svg_song">
	<img src="../img/mute.svg" id="svg_mute" class="invisible">
</div>

<script type="text/javascript" src="../js/script_song.js"></script>
</body>
</html>
';
	$nameo = str_replace(".xml", ".html", $name[$a]);
    file_put_contents("../html/".$nameo, $page);
    
    $a++;
}
?>
