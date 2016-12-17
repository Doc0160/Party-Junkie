$(document).ready(function(){
	var song = new Audio('https://doc0160.github.io/Party-Junkie/song/marioTheme.mp3');
    if(!('volume' in sessionStorage)) {
        sessionStorage.setItem("volume", 0.1);
    }
    if(!('mute' in sessionStorage)) {
        sessionStorage.setItem("mute", "false");
    }
    song.volume = Math.pow(parseFloat(sessionStorage.getItem("volume")), 2.0);
    song.loop = true;
    
    /*var p = function() {
        $('#svg_song').toggleClass('invisible');
        $('#svg_mute').toggleClass('invisible');
        if(sessionStorage.getItem("mute") == "true") {
            sessionStorage.setItem("mute", "false");
            song.play();
        } else {
            sessionStorage.setItem("mute", "true");
            song.pause();
        }
    };*/
    var pl = function(){
        $('#svg_song').removeClass('invisible');
        $('#svg_mute').addClass('invisible');
        sessionStorage.setItem("mute", "false");
        song.play();
    };
    var pa = function() {
        $('#svg_song').addClass('invisible');
        $('#svg_mute').removeClass('invisible');
        sessionStorage.setItem("mute", "true");
        song.pause();
    };
    if(sessionStorage.getItem("mute") == "true") {
        pl();
    } else {
        pa();
    }
	$('#svg_song').click(pa);
	$('#svg_mute').click(pl);
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
		    sessionStorage.setItem("volume", Math.min(1, parseFloat(sessionStorage.getItem("volume")) + 0.025));
	    } else {
		    sessionStorage.setItem("volume", Math.max(0, parseFloat(sessionStorage.getItem("volume")) - 0.025));
	    }
		console.log("Volume set to: " + sessionStorage.getItem("volume"));
        song.volume = Math.pow(parseFloat(sessionStorage.getItem("volume")), 2.0);
        e.preventDefault();
    }
})
