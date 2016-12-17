
$(document).ready(function(){
	var song = new Audio('https://doc0160.github.io/Party-Junkie/song/marioTheme.mp3');
    song.onunload = function(){
        sessionStorage.setItem("current_time", song.currentTime);
    };
    if(sessionStorage.getItem("volume") == null) {
        sessionStorage.setItem("volume", 0.1);
    }
    song.volume = Math.pow(parseFloat(sessionStorage.getItem("volume")), 2.0);
    
    if(sessionStorage.getItem("mute") == null) {
        sessionStorage.setItem("mute", "false");
    }
    if(sessionStorage.getItem("mute") == "false") {
        pl();
    } else {
        pa();
    }
    
    if(sessionStorage.getItem("current_time") == null) {
        sessionStorage.setItem("current_time", 0.0);
    }
    song.currentTime = parseFloat(sessionStorage.getItem("current_time"));
    song.loop = true;
    
    var pl = function(){
        $('#svg_song').removeClass('invisible');
        $('#svg_mute').addClass('invisible');
        sessionStorage.setItem("mute", "false");
        song.play();
    };
    var pa = function() {
        sessionStorage.setItem("current_time", song.currentTime);
        $('#svg_song').addClass('invisible');
        $('#svg_mute').removeClass('invisible');
        sessionStorage.setItem("mute", "true");
        song.pause();
    };
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
});
