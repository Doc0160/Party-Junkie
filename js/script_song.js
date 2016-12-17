$(document).ready(function(){
	var song = new Audio('https://doc0160.github.io/Party-Junkie/song/marioTheme.mp3');
    if(!('message' in sessionStorage)) {
        sessionStorage.setItem("volume", 0.1)
    }
    song.volume = Math.pow(sessionStorage.getItem("volume"), 2.0);
    song.loop = true;
    
    song.play();
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

    if(document.getElementById('svg_song').addEventListener){
		// IE9, Chrome, Safari, Opera
		document.getElementById('svg_song').addEventListener("mousewheel", cbScroll, false);
		// Firefox
		document.getElementById('svg_song').addEventListener("DOMMouseScroll", cbScroll, false);
	} else { // IE 6/7/8
		document.getElementById('svg_song').attachEvent("onmousewheel", cbScroll);
	}

    function cbScroll(e) {
	    var e = window.event || e;
	    var detail = Math.max(-1, Math.min(1, (e.wheelDelta || -e.detail)));
	    
	    if(detail > 0){
		    sessionStorage.setItem("volume", Math.min(1, sessionStorage.getItem("volume") + 0.025));
	    } else {
		    sessionStorage.setItem("volume", Math.max(0, sessionStorage.getItem("volume") - 0.025));
	    }
		console.log("Volume set to: " + sessionStorage.getItem("volume"));
        song.volume = Math.pow(sessionStorage.getItem("volume"), 2.0);
        e.preventDefault();
    }
})
