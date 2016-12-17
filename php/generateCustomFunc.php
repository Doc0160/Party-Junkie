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

?>
