<?php

$document = scandir('../json/');

for($i=2; $i<sizeof($document) ;$i++){
	$json = file_get_contents('../json/'.$document[$i]);
		
	//pour que le json soit conforme
	$json = str_replace("\n","",$json); 
	$json = str_replace("\r","",$json); 
	$json = str_replace("\t","",$json); 


	$json = json_decode($json, TRUE);

	for($j=0; $j<sizeof($json)-1;$j++){
		var_dump($json);
	}
}

?>