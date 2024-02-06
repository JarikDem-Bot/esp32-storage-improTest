const char *HTML_HOME_PAGE = R"(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Led Control</title>
    <style>
        * {
            margin: 0;
            padding: 0;
        }
        .container {
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: space-around;
        }
        .element {
            text-align: center;
            margin: 20px 0;
        }
        p {
            color: black;
            font-size: large;
            font-family: 'Franklin Gothic Medium', 'Arial Narrow', Arial, sans-serif;
        }
        button {
            background-color: #04AA6D;
            border: none;
            border-radius: 15px;
            color: white;
            padding: 15px 32px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 16px;
            transition-duration: 0.5s;
        }
        button:hover {
            box-shadow: 0 6px 12px 0 rgba(0,0,0,0.24), 0 10px 20px 0 rgba(0,0,0,0.19);
            transition-duration: 0.5s;
        }
        button:active {
            background-color: #027048;
        }
    </style>
</head>
<body>
    <div class="container">
        <p class="element state-text">Current led state: %LED_STATE%</p>
        <button class="toggle-led">Toggle</button>
    </div>

    <script>
        const state_text = document.querySelector(".state-text");
        const button = document.querySelector(".toggle-led");
        button.addEventListener("click", (e) => {
          fetch('/toggle-led', {
              method: 'POST',
              headers: {'Content-Type':'application/x-www-form-urlencoded'}, // this line is important, if this content-type is not set it wont work
              body: 'foo=bar&blah=1'
          })
          .then((rsp) => rsp.json())
          .then((obj) => {
            console.log(obj);
            console.log(obj.state);
            state_text.innerHTML = "Current led state: " + obj.state;
          });
          
        });
    </script>
</body>
</html>
)";
