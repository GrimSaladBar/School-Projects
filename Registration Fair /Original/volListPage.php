<?php
session_start(); 

if ($_SESSION['adminlogin']!="yes")
{
header("Location: index.html");
}
?>
<!DOCTYPE html>
<html style="font-size: 16px;">
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta charset="utf-8">
    <meta name="keywords" content="Ready To Try?">
    <meta name="description" content="">
    <meta name="page_type" content="np-template-header-footer-from-plugin">
    <title>Volunteer List Page</title>
    <link rel="stylesheet" href="nicepage.css" media="screen">
<link rel="stylesheet" href="Home.css" media="screen">
    <script class="u-script" type="text/javascript" src="jquery.js" defer=""></script>
    <script class="u-script" type="text/javascript" src="nicepage.js" defer=""></script>
    <meta name="generator" content="Nicepage 4.2.0, nicepage.com">
    <link id="u-theme-google-font" rel="stylesheet" href="https://fonts.googleapis.com/css?family=Roboto:100,100i,300,300i,400,400i,500,500i,700,700i,900,900i|Open+Sans:300,300i,400,400i,600,600i,700,700i,800,800i">
    <link id="u-page-google-font" rel="stylesheet" href="https://fonts.googleapis.com/css?family=Roboto:100,100i,300,300i,400,400i,500,500i,700,700i,900,900i">
    
    
    <script type="application/ld+json">{
		"@context": "http://schema.org",
		"@type": "Organization",
		"name": "",
		"logo": "images/logo.png"
}</script>
    <meta name="theme-color" content="#478ac9">
    <meta property="og:title" content="Template">
    <meta property="og:type" content="website">
  </head>
  <body data-home-page="template.html" data-home-page-title="Template" class="u-body"><header class="u-clearfix u-header u-header" id="sec-1b2e"><div class="u-clearfix u-sheet u-valign-middle u-sheet-1">
        <a href="mainmenu.php" class="u-image u-logo u-image-1">
          <img src="images/logo.png">
        </a>
        <nav class="u-menu u-menu-dropdown u-offcanvas u-menu-1">
          <div class="menu-collapse" style="font-size: 1rem; letter-spacing: 0px;">
            <a class="u-button-style u-custom-left-right-menu-spacing u-custom-padding-bottom u-custom-top-bottom-menu-spacing u-nav-link u-text-active-palette-1-base u-text-hover-palette-2-base" href="#">
              <svg viewBox="0 0 24 24"><use xmlns:xlink="http://www.w3.org/1999/xlink" xlink:href="#menu-hamburger"></use></svg>
              <svg version="1.1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink"><defs><symbol id="menu-hamburger" viewBox="0 0 16 16" style="width: 16px; height: 16px;"><rect y="1" width="16" height="2"></rect><rect y="7" width="16" height="2"></rect><rect y="13" width="16" height="2"></rect>
</symbol>
</defs></svg>
            </a>
          </div>
          <div class="u-nav-container">
            <ul class="u-nav u-unstyled u-nav-1"><li class="u-nav-item"><a class="u-button-style u-nav-link u-text-active-palette-1-base u-text-hover-palette-2-base" href="Home.html" style="padding: 10px 20px;"></a>
</li><li class="u-nav-item"><a class="u-button-style u-nav-link u-text-active-palette-1-base u-text-hover-palette-2-base" href="mainmenu.php" style="padding: 10px 20px;">Main Menu</a>
</li><li class="u-nav-item"><a class="u-button-style u-nav-link u-text-active-palette-1-base u-text-hover-palette-2-base" href="logout.php" style="padding: 10px 20px;">Log Out</a>
</li></ul>
          </div>
          <div class="u-nav-container-collapse">
            <div class="u-black u-container-style u-inner-container-layout u-opacity u-opacity-95 u-sidenav">
              <div class="u-inner-container-layout u-sidenav-overflow">
                <div class="u-menu-close"></div>
                <ul class="u-align-center u-nav u-popupmenu-items u-unstyled u-nav-2"><li class="u-nav-item"><a class="u-button-style u-nav-link" href="mainmenu.php">Main Menu</a>
</li><li class="u-nav-item"><a class="u-button-style u-nav-link" href="logout.php">Log Out</a>
</li></ul>
              </div>
            </div>
            <div class="u-black u-menu-overlay u-opacity u-opacity-70"></div>
          </div>
        </nav>
      </div></header>
    <section class="u-clearfix u-section-1" id="carousel_0d8a">
      <div class="u-clearfix u-expanded-width u-layout-wrap u-layout-wrap-1">
        <div class="u-layout">
          <div class="u-layout-row">
            <div class="u-align-left u-container-style u-image u-layout-cell u-size-30 u-image-1" data-image-width="1125" data-image-height="750">
              <div class="u-container-layout u-container-layout-1"></div>
            </div>
            <div class="u-align-center u-container-style u-grey-5 u-layout-cell u-size-30 u-layout-cell-2">
              <div class="u-container-layout u-valign-middle u-container-layout-2">
                <?php
      $servername = "localhost";
	  $username = "root";
	  $password = "";
	  $dbname = "final examination";
	  
	  //create connection
	  $conn = mysqli_connect($servername,$username,$password,$dbname);
	  
	  //Check connection
	  if(!$conn)
	     {
		    die("Connection failed:".mysqli_connect_error());
		}
		
		//Query the table
		$result = mysqli_query($conn,"SELECT*From volunteers ORDER BY lastname ASC");
		
		//print the table contents
		if($result->num_rows>0)
		{
	echo "<table border='1'>
                    <tr>
                 <th>ID</th>
                    <th>First Name</th>
                    <th>Last Name</th>
					<th>Telephone</th>
					<th>Volunteer Option</th>
					<th>confirmedField</th>
                   
                            </tr>";
		//output data of each row
		while($row = $result->fetch_assoc())
	
                    {
                              echo "<tr>";
                          echo "<td>" . $row['id'] . "</td>";
                           echo "<td>" . $row['firstname'] . "</td>";
						   echo "<td>" . $row['lastname'] . "</td>";
						   echo "<td>" . $row['telephone'] . "</td>";
						    echo "<td>" . $row['volunteerOption'] . "</td>";
							 echo "<td>" . $row['confirmedField'] . "</td>";
                                   echo "</tr>";
								   
                    }
					echo "</table>";
		} 
		else
		{
		echo"0 results";
		}
		mysqli_close($conn)
		
		?>
		
		
		<?php
        $servername = "localhost";
      $username = "root";
      $password = "";
      $dbname = "final examination";


      //create connection
      $conn = mysqli_connect($servername,$username,$password,$dbname);
       $result1 = mysqli_query($conn, "SELECT  COUNT(*) as count
            FROM volunteers ");
      $result = mysqli_query($conn, "SELECT  COUNT(*) as count
            FROM volunteers where confirmedField = 'yes'");

while ($row = mysqli_fetch_array($result)) {

    $var = $row['count'];
}

       echo "<br>There is/are currently ($var)";
   echo" confirmed volunteer(s).";




       while ($row1 = mysqli_fetch_array($result1)) {

    $var1 = $row1['count'];
}
         if($var1 < 5){
        echo"<br>";
        echo"<br>";
		echo"There is/are currently";echo "<span style=\"color:red;\">($var1)</span>";
		echo"volunteer(s).";
         }
       else {    echo "<br><br>There is/are currently " .$var1. "  volunteer(s).";}
       mysqli_close($conn)
       ?>
              </div>
            </div>
          </div>
        </div>
      </div>
    </section>
	 <footer class="u-align-center u-clearfix u-footer u-grey-80 u-footer" id="sec-ccac">
	<br>
		<!-- Footer Stuff goes here -->
			<img src="images/logoFooter.png" style="height:120px;" usemap="#HomeLogo"/>
			<Map name="HomeLogo">
				<area shape = "rect" coords="0,0,344,111" href="mainmenu.php"/>
			</map>
			<h3> M A N Y &nbsp; S T U D I E S - O N E &nbsp; C O M M U N I T Y </h3>
			<p style="font-weight:bold"> Mission Statement </p>
			<p style="font-size:14px"> To meet the changing developmental, educational and training needs of stakeholders through the provision of relevant, high-quality programmes </p>
			<p style="font-weight:bold"> Vision </p>
			<p style="font-size:14px"> To be a world-class centre of excellence in education and training. </p>
			<p><a href="https://www.bcc.edu.bb/Divisions/" style="color:cyan">DIVISIONS</a> &nbsp; <a href="https://www.bcc.edu.bb/Administration/" style="color:cyan">ADMINISTRATION & DEPARTMENTS</a></p>
			<br/>
			<p><a href="https://www.bcc.edu.bb/Contact/" style="color:cyan">Contact Us</a> |&nbsp; <a href="https://www.bcc.edu.bb/Directory/" style="color:cyan">Directory</a> |&nbsp; <a href="https://www.bcc.edu.bb/Directions/" style="color:cyan">Maps & Directions</a></p>
			<p>"Eyrie", Howell's Cross Road, St. Michael, Barbados, W.I., BB11058</p>
			<p>📞(246) 426-2858 ☏(246) 429-5435</p>
			<br/>
			<p>&#169; 2021 Barbados Community College. All rights reserved</p>
			<p><a href="https://www.bcc.edu.bb/Terms/" style="color:cyan">Terms of Use</a> &nbsp; <a href="https://www.bcc.edu.bb/Privacy/" style="color:cyan">Privacy Policy</a></p>
		</footer>
    <section class="u-backlink u-clearfix u-grey-80">
      <a class="u-link" href="https://nicepage.com/website-templates" target="_blank">
        <span>Website Templates</span>
      </a>
      <p class="u-text">
        <span>created with</span>
      </p>
      <a class="u-link" href="" target="_blank">
        <span>Website Builder Software</span>
      </a>. 
    </section>
  </body>
 </html>