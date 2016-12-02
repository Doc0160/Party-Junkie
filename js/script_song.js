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

    if($('#svg_song').addEventListener)
	    {
		    // IE9, Chrome, Safari, Opera
		    $('#svg_song').addEventListener("mousewheel", cbScroll, false);
		    // Firefox
		    $('#svg_song').addEventListener("DOMMouseScroll", cbScroll, false);
	    }
	// IE 6/7/8
	else
	    {
		    $('#svg_song').attachEvent("onmousewheel", cbScroll);
	    }

    
    function cbScroll(e)
    {
	    var e = window.event || e;
	    var detail = Math.max(-1, Math.min(1, (e.wheelDelta || -e.detail)));
	    
	    if(detail > 0)
	        {
		        volume = Math.min(1, volume + 0.025);
	        }
	    else
	        {
		        volume = Math.max(0, volume - 0.025);
	        }
	    
	    if(audioGainNode != null)
	        {
		        console.log("Volume set to: " + volume);
                song.volume = Math.pow(volume, 2.0);
		        //audioGainNode.gain.value = Math.pow(volume, 2.0); // makes the volume more realistic
	        }
	    
	    volumeAnimation = 400;
    }
})
