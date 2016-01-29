function startRodgersApp(){
      // CREATE A REFERENCE TO FIREBASE
      var dbRef = new Firebase("https://experiment614.firebaseio.com");

      // REGISTER DOM ELEMENTS
      var messageField = $('#messageInput');
      var nameField = $('#nameInput');
      var messageList = $('#example-messages');

      // LISTEN FOR KEYPRESS EVENT
      messageField.keypress(function (e) {
        if (e.keyCode == 13) {
          //FIELD VALUES
          var username = nameField.val();
          var message = messageField.val();

          if (username === ""){
            username = getSillyName();
            nameField.val(username); 
          }

          //SAVE DATA TO FIREBASE AND EMPTY FIELD
          if(message != ""){
            dbRef.child("messages").push({name:username, text:message});
          }
          messageField.val('');
        }
      });

      // Add a callback that is triggered for each chat message.
      dbRef.child("messages").limitToLast(35).on('child_added', function (snapshot) {
        //GET DATA
        var data = snapshot.val();
        var username = data.name;
        var message = data.text;

        //CREATE ELEMENTS MESSAGE & SANITIZE TEXTs
        var messageElement = $("<li>");
        var nameElement = $("<strong class='username-style'></strong>")
        nameElement.text(username + ":   ");
        messageElement.text(message).prepend(nameElement);

        //ADD MESSAGE
        messageList.append(messageElement)

        //SCROLL TO BOTTOM OF MESSAGE LIST
        messageList[0].scrollTop = messageList[0].scrollHeight;
      });


      // REGISTER DOM ELEMENTS
      var urlField = $('#urlInput');
      var titleField = $('#titleInput');
      var messageFieldNote = $('#messageInputNote');

      var saveNoteNow = function() {
        //FIELD VALUES
        var url = urlField.val() || getMrRodgers();
        var title = titleField.val();
        var message = messageFieldNote.val();
        var timestamp = Firebase.ServerValue.TIMESTAMP;
        console.log("URL: ", url);
        console.log("title: ", title);
        console.log("message: ", message);

        //SAVE DATA TO FIREBASE AND EMPTY FIELD
        // add a timestamp section to this...
        if (title != "" && message != ""){
          dbRef.child("notes").push({url:url, title:title, message:message, up:"0", down:"0", timestamp:timestamp});
        }
        urlField.val('');
        titleField.val('');
        messageFieldNote.val('');
      };

      // Send new note to db on enter in message
      messageFieldNote.keypress(function (e) {
        if (e.keyCode == 13) {
          saveNoteNow();
        }
      });

      // Send new note to db on button click
      $(document).ready(function(){
        $('#saveNote').click(function(){
          saveNoteNow();
        });
      });

      // Add a callback that is triggered for each note on the board
      dbRef.child("notes").limitToLast(10).on('child_added', function (snapshot) {
        
        var data = snapshot.val();
        var url = data.url; // call some function if this is null
        var title = data.title;
        var message = data.message;
        var up = data.up;
        var down = data.down;
        var timestamp = data.timestamp;

        $("#note-insert")
          .append(




          );
      });      


      // Message area container controll //
      $(function() {  
         var window_height = $(window).height(),
         content_height = window_height;
         $('.sidebar-chat').height(content_height/1.01 - 135);
         $('.messages').height(content_height/1.01 - 200);
      });

      $( window ).resize(function() {
         var window_height = $(window).height(),
         content_height = window_height;
         $('.sidebar-chat').height(content_height/1.01 - 135);
         $('.messages').height(content_height/1.01 - 200);
      });


      function getMrRodgers() {
        var urLinks = [
          "http://24.media.tumblr.com/tumblr_m6dr32ysWp1rodz1bo1_1280.jpg",
          "http://cdn1.relevantmediagroup.com/sites/default/files/field/thumbnail/mr_rogers_thumb.jpg",
          "http://i.huffpost.com/gen/1046678/thumbs/o-MISTER-ROGERS-BIRTHDAY-570.jpg?6",
          "http://www.legacy.com/UserContent/ns/Photos/Mr.%20Rogers.jpg",
          "http://23g9r82i3f1d2a63qz3akhv1.wpengine.netdna-cdn.com/wp-content/blogs.dir/53/files/2003/03/ch0305fred-rogers.jpg",
          "http://media.salon.com/2015/07/fredrogers-690x460-1.jpg",
          "http://www.whut.org/whut/wp-content/uploads/2012/06/Mr-Rogers-900-600-600x4001.jpg",
          "http://www.ew.com/sites/default/files/i/2013/05/02/Mister-Rogers-Neighborhood.jpg",
          "http://40.media.tumblr.com/176e341ff63c917015101fc07ff3eef6/tumblr_mjys4fEXQB1rgswbro1_1280.jpg",
          "http://i.ytimg.com/vi/W12NxRQdSb8/hqdefault.jpg",
          "http://a3.files.biography.com/image/upload/c_fit,cs_srgb,dpr_1.0,h_1200,q_80,w_1200/MTI4NjkzOTUwNDI3OTkzMzYy.jpg",
          "http://media1.popsugar-assets.com/files/2011/08/34/1/192/1922507/074aa2be385d05c9_MrRogerssq/i/Dress-Like-Mister-Rogers.jpg",
          "http://i.imgur.com/8YA0g.jpg",
          "http://images.mentalfloss.com/sites/default/files/styles/article_640x430/public/mister_rogers_music.jpg",
          "http://i.ytimg.com/vi/Xg782MyVnDU/hqdefault.jpg",
          "http://www.theblaze.com/wp-content/uploads/2012/06/fred-rogers1.jpg",
          "https://encrypted-tbn3.gstatic.com/images?q=tbn:ANd9GcRaZdEeLmLqn6lKBKifVczlbOCSA72SJNDCZ56WEYp-R1rMCNex",
          "http://remixtheory.net/remixImages/mrRogersRemix.jpg",
          "http://images1.wikia.nocookie.net/__cb20060503125140/muppet/images/9/91/Mrrogers.jpg",
          "https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQK9zr8PPpuG3Ba3rSqsbo-Ml28Tp6SoWqZMt0iiA87VmzbZtFfIw",
          "https://s-media-cache-ak0.pinimg.com/236x/63/0b/fe/630bfe09b50888ed96e9ce05ab252af3.jpg",
          "https://i.imgflip.com/kqtw4.jpg",
          "http://www.geekfill.com/wp-content/uploads/2013/06/Good-Guy-Mr.-Rogers.jpg",
          "http://i.imgur.com/fbjJD8q.png",
          "http://s2.quickmeme.com/img/fa/fa1d1d10eca9ec8d265b84a03c2e241c99793721427eb42178bd889b447557e8.jpg",
          "http://www.mememaker.net/static/images/templates/117944.jpg",
          "http://bp1.blogger.com/_qMBUlM_SEWE/R8ce_nOmNNI/AAAAAAAAAfM/OJR-80FnKDM/s320/rogersfred.jpg",
          "http://tattooroadtrip.com/blog/wp-content/uploads/2013/07/imgres.jpg",
          "http://4.bp.blogspot.com/_CNPZ0JYfo5Y/THs4g4O3CKI/AAAAAAAAP48/pJmwLVIcNyI/s1600/MrRogers.jpg",
          "http://www.blogcdn.com/www.parentdish.com/media/2008/08/mr-rogers-pbs-canceled.jpg",
          "http://file2.answcdn.com/answ-cld/image/upload/w_726,c_fill,g_faces:center,q_60/v1/tk/view/cew/999ffc06/6799428f5d506887c2bd084dc9d4f86969c7db0f.jpeg"
        ];

        return  urLinks[Math.floor(Math.random()*urLinks.length)];
      }

      // Name Generator
      function getSillyName() {
        var firstName = ["Runny", "Buttercup", "Dinky", "Stinky", "Crusty",
        "Greasy","Gidget", "Cheesypoof", "Lumpy", "Wacky", "Tiny", "Flunky",
        "Fluffy", "Zippy", "Doofus", "Gobsmacked", "Slimy", "Grimy", "Salamander",
        "Oily", "Burrito", "Bumpy", "Loopy", "Snotty", "Irving", "Egbert","Waffer", 
        "Lilly","Rugrat","Sand", "Fuzzy","Kitty", "Puppy", "Snuggles","Rubber", 
        "Stinky", "Lulu", "Lala", "Sparkle", "Glitter", "Silver", "Golden", "Rainbow", 
        "Cloud", "Rain", "Stormy", "Wink", "Sugar", "Twinkle", "Star", "Halo", "Angel"];

        var lastName1 = ["Snicker", "Buffalo", "Gross", "Bubble", "Sheep",
         "Corset", "Toilet", "Lizard", "Waffle", "Kumquat", "Burger", "Chimp", "Liver",
         "Gorilla", "Rhino", "Emu", "Pizza", "Toad", "Gerbil", "Pickle", "Tofu", 
        "Chicken", "Potato", "Hamster", "Lemur", "Vermin"];

        var lastName2 = ["face", "dip", "nose", "brain", "head", "breath", 
        "pants", "shorts", "lips", "mouth", "muffin", "butt", "bottom", "elbow", 
        "honker", "toes", "buns", "spew", "kisser", "fanny", "squirt", "chunks", 
        "brains", "wit", "juice", "shower"];

        return  firstName[Math.floor(Math.random()*firstName.length)] 
                + " " + lastName1[Math.floor(Math.random()*lastName1.length)]
                + lastName2[Math.floor(Math.random()*lastName1.length)];
         }
}