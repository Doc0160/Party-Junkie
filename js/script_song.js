
$(document).ready(function(){
    var ec = new Evercookie();
	var song = new Audio('https://doc0160.github.io/Party-Junkie/song/marioTheme.mp3');
    $(song).onbeforeunload = function(){
        ec.set("current_time", song.currentTime);
        alert(song.currentTime);
    };
    if(!('volume' in ec)) {
        ec.set("volume", 0.1);
    }
    if(!('mute' in ec)) {
        ec.set("mute", "false");
    }
    if(!('current_time' in ec)) {
        ec.set("current_time", 0);
    }
    song.volume = Math.pow(parseFloat(ec.get("volume")), 2.0);
    song.loop = true;
    
    var pl = function(){
        $('#svg_song').removeClass('invisible');
        $('#svg_mute').addClass('invisible');
        ec.set("mute", "false");
        song.play();
    };
    var pa = function() {
        ec.set("current_time", song.currentTime);
        $('#svg_song').addClass('invisible');
        $('#svg_mute').removeClass('invisible');
        ec.set("mute", "true");
        song.pause();
    };
    if(ec.get("mute") == "false") {
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
		    ec.set("volume", Math.min(1, parseFloat(ec.get("volume")) + 0.025));
	    } else {
		    ec.set("volume", Math.max(0, parseFloat(ec.get("volume")) - 0.025));
	    }
		console.log("Volume set to: " + ec.get("volume"));
        song.volume = Math.pow(parseFloat(ec.get("volume")), 2.0);
        e.preventDefault();
    }
});
