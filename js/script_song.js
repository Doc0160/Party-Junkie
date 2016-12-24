
$(document).ready(function(){
	var song = new Audio('https://doc0160.github.io/Party-Junkie/song/marioTheme.mp3');
    song.onunload = function(){
        localStorage.setItem("current_time", song.currentTime);
    };
    if(localStorage.getItem("volume") == null) {
        localStorage.setItem("volume", 0.1);
    }
    song.volume = Math.pow(parseFloat(localStorage.getItem("volume")), 2.0);

    var pl = function(){
        $('#svg_song').removeClass('invisible');
        $('#svg_mute').addClass('invisible');
        localStorage.setItem("mute", "false");
        song.play();
    };
    var pa = function() {
        localStorage.setItem("current_time", song.currentTime);
        $('#svg_song').addClass('invisible');
        $('#svg_mute').removeClass('invisible');
        localStorage.setItem("mute", "true");
        song.pause();
    };
    
    if(localStorage.getItem("mute") == null) {
        localStorage.setItem("mute", "false");
    }
    if(localStorage.getItem("mute") == "false") {
        pl();
    } else {
        pa();
    }
    
    if(localStorage.getItem("current_time") == null) {
        localStorage.setItem("current_time", 0.0);
    }
    song.currentTime = parseFloat(localStorage.getItem("current_time"));
    song.loop = true;
    
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
		    localStorage.setItem("volume", Math.min(1, parseFloat(localStorage.getItem("volume")) + 0.025));
	    } else {
		    localStorage.setItem("volume", Math.max(0, parseFloat(localStorage.getItem("volume")) - 0.025));
	    }
		console.log("Volume set to: " + localStorage.getItem("volume"));
        song.volume = Math.pow(parseFloat(localStorage.getItem("volume")), 2.0);
        e.preventDefault();
    }
});
