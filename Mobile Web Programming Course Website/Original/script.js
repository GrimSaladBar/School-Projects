function askFirst() {
    let text = "You are about to be redirected to an external webpage!\nChoose either YES or NO.";
    if (confirm(text) == true) {
        window.location.href = "https://uwi.edu/softwareengineering/details.html";
    }
}

var watchID;
var geoLoc;
var amPM;

function showLocation(position) {
    var timestamp = position.timestamp;
    var time = new Date(timestamp);

    var hours = time.getHours(),
    minutes = time.getMinutes(),
    seconds = time.getSeconds(),
    month = time.getMonth() + 1,
    day = time.getDate(),
    year = time.getFullYear() % 100;

    if (hours < 12) {
        amPM = "AM";
    }
    else if (hours <= 12) {
        amPM = "PM"
    }

    function pad(time) {
        return (time < 10 ? "0" : "") + time;
    }

    var formattedDate = "Accessed On: " + pad(month) + "/" + pad(day) + "/" + pad(year) + " at: " + pad(hours) + ":" + pad(minutes) + " " + amPM

    localStorage.setItem('date',formattedDate);
    document.getElementById("access").innerHTML = formattedDate;
}

function errorHandler(err) {
    if (err.code == 1) {
        alert ("Error: Access is denied!");
    }
    else if (err.code == 2) {
        alert ("Error: Position is unavilable!");
    }
}

function getLocation() {
    if (navigator.geolocation) {
        geoLoc = navigator.geolocation;
        watchID = geoLoc.getCurrentPosition(showLocation, errorHandler);
    }
    else {
        alert ("Sorry, browser does not support geolocation!");
    }
}

function displayAccess() {
    document.getElementById("access").innerHTML = localStorage.getItem('date');
}

/*************From W3Schools*************/
/* Set the width of the side navigation to 250px */
function openNav() {
    document.getElementById("mySidenav").style.width = "250px";
    document.body.style.backgroundColor = "rgba(0,0,0,0.4)";
}
  
/* Set the width of the side navigation to 0 */
function closeNav() {
    document.getElementById("mySidenav").style.width = "0";
    document.body.style.backgroundColor = "white";
}

function allowDrop(ev) {
    ev.preventDefault();
}
  
function drag(ev) {
    ev.dataTransfer.setData("text", ev.target.id);
}

function drop(ev) {
    ev.preventDefault();
    var data = ev.dataTransfer.getData("text");
    ev.target.appendChild(document.getElementById(data));
}