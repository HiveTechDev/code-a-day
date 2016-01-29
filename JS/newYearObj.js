

function Year() {

    this.perspectiveOnYear = false;
    this.changePerspective = function (perspective) {
        this.perspectiveOnYear = perspective;
    };

    this.getPerspective = function(){
        return this.perspectiveOnYear;
    };

    this.printPerspective = function(){
        return (this.perspectiveOnYear) ? console.log("Have a happy year!") : console.log("Have a bad year!");
    };
}

var twentySixteen = new Year()

twentySixteen.printPerspective()
//Have a bad year!

console.log(twentySixteen.getPerspective());
//Have a bad year!

twentySixteen.changePerspective(true)

twentySixteen.printPerspective()
//Have a happy year!

//git config --global user.email "your_email@example.com"
// This email didn't match the github email so it didnt show up on the calendar
//https://help.github.com/articles/why-are-my-contributions-not-showing-up-on-my-profile/