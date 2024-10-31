/*******************************/
/*******************************/
/*********MAIN FUNCTIONS********/
/*******************************/
/*******************************/

/**
* loadData function for Assignment #1
*
* Add this function to your external JavaScript file. The simplest way to invoke it is
* to use the onload eventhandler on the body tag of the document, i.e. <body onload="loadData()">.
* If successful, you should be able to see three sets of data in localStorage the first is 
* trainer information (trainers), the second is manager information (managers) and the third is the member information (members).
* Feel free to modify this code to suit your field names if necessary.
*/
function loadData(){
    var trainers = [
        {
            email: "a.pryor@fitnessu.life",
            firstName: "Andrew",
            lastName: "Pryor",
            password:"@ndr#wPry0r123"
        },

        {
            email: "jjd@fitnessuniverse.com",
            firstName: "Jennifer",
            lastName: "Davis",
            password:"Anoth3rpa$$"
        },
        
        {
            email: "boss_man@fitnessuniverse.bb",
            firstName: "Anderson",
            lastName: "Alleyne",
            password:"Pa$sw0rd"
        }
    ]

    var managers = [
        {
            email: "todd.phillips@fitnessu.life",
            firstName: "Todd",
            lastName: "Phillips",
            password:"M3nt10#@1T"
        },

        {
            email: "marsh.fredrick@fitnessuniverse.com",
            firstName: "Marsh",
            lastName: "Fredrick",
            password:"gRenT1l$@l3"
        },

        {
            email: "gene.rodenberry@fitnessuniverse.bb",
            firstName: "Gene",
            lastName: "Rodenberry",
            password:"th3#@st3RPl@n"
        }
    ]

    var members = [
        {
            year: "2018",
            memberId: "949309",
            firstName: "Merissa",
            lastName: "Halliwall",
            email: "mm_h@hotmail.com",
            password:"f1rstPa$$",
            address: "Lodge Road Ch Ch"
        },

        {
            year: "2019",
            memberId: "901440",
            firstName: "Terold",
            lastName: "Bostwick",
            email: "terold.bostwick@gmail.com",
            password:"Secur3@cc3s5",
            address: "7 Jasmine Ridge St James"
        },
        
        {
            year: "2020",
            memberId: "940830",
            firstName: "Vanda",
            lastName: "Marshall",
            email: "vmarhsall@guardian.co.uk",
            password:"Oll1p&p$",
            address: "Sargeants Village Tenantry Ch Ch"
        },

        {
            year: "2018",
            memberId: "910948",
            firstName: "Winston",
            lastName: "Greaves",
            email: "winston@bimap.gov.bb",
            password:"f03verP@ssword",
            address: "33 Welches Terrace"
        },

        {
            year: "2019",
            memberId: "921035",
            firstName: "Mark",
            lastName: "Belgrave",
            email: "bboy89@hotmail.com",
            password:"246Bajan#1",
            address: "76 Edghill Terrace"
        },

        {
            year: "2020",
            memberId: "906059",
            firstName: "Pamalee",
            lastName: "Gaskin",
            email: "pamgask99@gmail.com",
            password:"pamal3G#$k",
            address: "Lot 33 The Belle"
        }
    ]
  
    //add to localStorage 
    if(!localStorage.getItem("trainers"))
    {
        localStorage.setItem("trainers", JSON.stringify(trainers));
    }
    if(!localStorage.getItem("managers"))
    {
        localStorage.setItem("managers", JSON.stringify(managers));
    }
    if(!localStorage.getItem("members"))
    {
        localStorage.setItem("members", JSON.stringify(members));
    }

}

function loginMember(data){
    var id = data.id.value;
    var passwd = data.passwd.value;

    var memIDCheck = verifyMemberNumber(id);
    var passwdCheck = verifyPassword(passwd);
    var invalidVisibility = document.getElementById('invalidUserError');

    //error message here - [CHANGE THIS TO A SINGLE ERROR FUNCTION THAT ACCEPTS MESSAGES THAT WILL BE OUTPUT TO HTML]
    memberIDError(memIDCheck);
    passwordError(passwdCheck);

    var memberArr = JSON.parse(localStorage.getItem("members"));
    //If the input passes both checks
    if (memIDCheck && passwdCheck){
        var isValidUser = checkMemberArray(id, passwd, memberArr);
        if (isValidUser == true){
            //error message here - [CHANGE ERROR MESSAGE HERE]
            invalidVisibility.style.display = 'none';
            sessionStorage.setItem('memberId', id);
            sessionStorage.setItem('firstName', getMemberFirstName(id, passwd, memberArr));
            sessionStorage.setItem('lastName', getMemberLastName(id, passwd, memberArr));
			sessionStorage.setItem('userType', 'member');
			sessionStorage.setItem('login', 'yes');
            divertUser('member');
        }
    }
    else
        //error message here - [CHANGE ERROR MESSAGE HERE]
        invalidVisibility.style.display = 'block';
}

function loginEmployee(data){
    var email = data.email.value;
    var passwd = data.passwd.value;

    var emailCheck = verifyEmail(email);
    var passwdCheck = verifyPassword(passwd);

    var invalidVisibility = document.getElementById('invalidUserError');

    //error message here - [CHANGE THIS TO A SINGLE ERROR FUNCTION THAT ACCEPTS MESSAGES THAT WILL BE OUTPUT TO HTML]
    emailError(emailCheck);
    passwordError(passwdCheck);

	var employeeType;
    var employeeArr;
    if (document.getElementById('employee').value == 'trainer'){
        employeeArr = JSON.parse(localStorage.getItem("trainers"));
		employeeType = 'trainer';
	}
    else if (document.getElementById('employee').value == 'manager'){
        employeeArr = JSON.parse(localStorage.getItem("managers"));
		employeeType = 'manager';
	}

    if (employeeArr){
        //If the input passes both checks
        if (emailCheck && passwdCheck){
            var isValidUser = checkEmployeeArray(email, passwd, employeeArr);
            if (isValidUser){
                //error message here - [CHANGE ERROR MESSAGE HERE]
                invalidVisibility.style.display = 'none';
                sessionStorage.setItem('email', email);
                sessionStorage.setItem('firstName', getEmployeeFirstName(email, passwd, employeeArr));
                sessionStorage.setItem('lastName', getEmployeeLastName(email, passwd, employeeArr));
				sessionStorage.setItem('userType', employeeType);
				sessionStorage.setItem('login', 'yes');
                divertUser(employeeType);
            }
        }
        else{
            //error message here - [CHANGE ERROR MESSAGE HERE]
            invalidVisibility.style.display = 'block';
        }
    }
}

function verifyMemberNumber(mid){
    if (mid.length != 6)
        return false;
    
    if (mid.charAt(0) != '9')
                return false;

    for (var i = 0; i < mid.length; i++){ 
        if (isNaN(mid.charAt(i)))
            return false;
    }
    return true;
}

function verifyEmail(email){
    if (!email.includes('@'))
        //error message here - [ADD ERROR MESSAGE HERE]
        return false;
    else{
        if (checkEmailDomain(email))
            return true;
        else
            //error message here - [ADD ERROR MESSAGE HERE]
            return false;
    }
}

function verifyPassword(pwd){
    if (pwd.length < 8 || pwd.length > 16){
        return false;
    }

    var upperCheck = false;
    var specialCheck = false;
    var numCheck = false;

    for (var i = 0; i < pwd.length; i++){
        //Essentially the same as writing (upperCheck == false)
        if (!upperCheck)
            upperCheck = checkUpperCase(pwd.charAt(i));
        if (!specialCheck)
            specialCheck = checkSpecialChar(pwd.charAt(i));
        if (!numCheck)
            numCheck = checkNumber(pwd.charAt(i));
    }

    //Checks to see if any required elements in the formatting are missing
    if (!upperCheck || !specialCheck || !numCheck)
        return false;
    else
        return true;
}

function findLostPassword(event){
    event.preventDefault(); // Prevent the form from reloading the webpage
    var employeeType = document.getElementById('employee').value;

    if (employeeType == 'trainer'){
        var email = document.getElementById('forgotTrainer').value;
        employeeType = 'trainers';
    }
    else if (employeeType == 'manager'){
        var email = document.getElementById('forgotManager').value;
        employeeType = 'managers';
    }
    var emailCheck = verifyEmail(email);
    if (emailCheck){
        var emailArr = JSON.parse(localStorage.getItem(employeeType));
        if (checkEmployeeEmail(email, emailArr)){
            //CSS PopUp HERE - [Replace with CSS POPUP]
            alert('Recovery link sent');
        }
        else{
            //CSS PopUp HERE - [Replace with CSS POPUP]
            alert('No account associated with email: ' + email);
        }
    }
}

function checkLogin(){
	var login = sessionStorage.getItem('login');

    if (login != 'yes'){
        window.location.href = 'index.html';
    }
}

function signOut(){
    var user = sessionStorage.getItem('userType');

    if (user == 'manager'){
        sessionStorage.clear;
        window.location.href = 'admin_login.html';
    }
    else if (user == 'trainer'){
        sessionStorage.clear;
        window.location.href = 'trainer_login.html';
    }  
    else{
        sessionStorage.clear;
        window.location.href = 'member_login.html';
    }
}

/*******************************/
/*******************************/
/**********SUB FUNCTIONS********/
/*******************************/
/*******************************/
function displayCurrentUser(){
    var firstName = sessionStorage.getItem('firstName');
    var lastName = sessionStorage.getItem('lastName');

    document.getElementById('loginName').innerHTML = 'Name: ' + firstName + ' ' + lastName;

    if (!sessionStorage.getItem('email'))
        document.getElementById('loginID').innerHTML = 'Member ID: ' + sessionStorage.getItem('memberId');
    else 
        document.getElementById('loginID').innerHTML = 'Email: ' + sessionStorage.getItem('email');
}

function divertUser(userType){
	if (userType == 'manager')
            window.location.href = 'admin_members.html';
    else if (userType == 'trainer')
            window.location.href = 'trainer_client.html';
    else
            window.location.href = 'member_console.html';
}

function submitFormMember(event){
    event.preventDefault(); // Prevent the form from reloading the webpage
    const data = {
        id: document.getElementById('memberID'),
        passwd: document.getElementById('memberPasswd')
    }
    
    loginMember(data);
}

function submitFormTrainer(event){
    event.preventDefault(); // Prevent the form from reloading the webpage
    const data = {
        email: document.getElementById('trainerEmail'),
        passwd: document.getElementById('trainerPasswd')
    }
    
    loginEmployee(data);
}

function submitFormManager(event){
    event.preventDefault(); // Prevent the form from reloading the webpage
    const data = {
        email: document.getElementById('managerEmail'),
        passwd: document.getElementById('managerPasswd')
    }
    
    loginEmployee(data);
}


function checkUpperCase(passwdChar){
    if (passwdChar == passwdChar.toUpperCase())
        return true;
    else
        return false;
}

function checkNumber(passwdChar){
    //This if statement outputs false if the input is NOT a number, and outputs true if the input IS a number
    if (!isNaN(passwdChar))
        return true;
    else
        return false;
}

function checkSpecialChar(passwdChar){
    //This switch returns false if the input does NOT contain one of the required special characters
    switch (passwdChar){
        case '&':
            return true;
        case '$':
            return true;
        case '#':
            return true;
        case '@':
            return true;
        default:
            return false;
    }
}

function checkMemberArray(id, passwd, array){
    for (var i = 0; i < array.length; i++){
            if (id == array[i].memberId && passwd == array[i].password)
                return true;
    }
    return false;
}

function checkEmployeeArray(email, passwd, array){
    for (var i = 0; i < array.length; i++){
            if (email == array[i].email && passwd == array[i].password)
                return true;
    }
    return false;
}

function checkEmployeeEmail(email, array){
    for (var i = 0; i < array.length; i++){
            if (email == array[i].email)
                return true;
    }
    return false;
}

function getMemberFirstName(id, passwd, array){
    for (var i = 0; i < array.length; i++){
            if (id == array[i].memberId && passwd == array[i].password)
                return array[i].firstName;
    }
}

function getMemberLastName(id, passwd, array){
    for (var i = 0; i < array.length; i++){
            if (id == array[i].memberId && passwd == array[i].password)
                return array[i].lastName;
    }
}

function getEmployeeFirstName(email, passwd, array){
    for (var i = 0; i < array.length; i++){
            if (email == array[i].email && passwd == array[i].password)
                return array[i].firstName;
    }
}

function getEmployeeLastName(email, passwd, array){
    for (var i = 0; i < array.length; i++){
            if (email == array[i].email && passwd == array[i].password)
                return array[i].lastName;
    }
}

function checkEmailDomain(email){
    var domain = email.split('@').pop();

    switch(domain){
        case ('fitnessuniverse.com'):
            return true;
        case ('fitnessuniverse.bb'):
            return true;
        case ('fitnessu.life'):
            return true;
        default:
            return false;
    }
}

function memberIDError(memIDCheck){
    if (!memIDCheck)
        document.getElementById('usernameFormatError').style.display = 'block';
    else
        document.getElementById('usernameFormatError').style.display = 'none';
}

function emailError(emailCheck){
    if (!emailCheck)
        document.getElementById('emailFormatError').style.display = 'block';
    else
        document.getElementById('emailFormatError').style.display = 'none';
}

function passwordError(passwdCheck){
    if (!passwdCheck)
        document.getElementById('passwdFormatError').style.display = 'block';
    else
        document.getElementById('passwdFormatError').style.display = 'none';
}