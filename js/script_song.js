$(document).ready(function(){
	var song = new Audio('https://doc0160.github.io/Party-Junkie/song/marioTheme.mp3');

	$('#svg_song').click(function(){
		$('#svg_song').toggleClass('invisible');
		$('#svg_mute').removeClass();
		song.pause();
	})

	$('#svg_mute').click(function(){
		$('#svg_mute').toggleClass('invisible');
		$('#svg_song').removeClass();
		song.play();
	})
	console.log('ok');

})
