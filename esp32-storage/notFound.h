const char *HTML_NOTFOUND_PAGE = R"===(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 Storage</title>

    <style>
        * {
            margin: 0;
            padding: 0;
        }

        html {
            font-family: sans-serif;
        }

        body {
            background: #282828;
            color: #cccccc;
        }

        .container {
            background: #3f3f3f;
            margin: 0 auto;
            padding: 20px;
            border: 1px solid black;
            width: auto;
            min-height: 20vh;

            display: flex;
            justify-content: space-around;
            flex-direction: column;
            align-items: center;
        }

        button {
            background-color: #372a54;
            padding: 5px 10px;
            border-radius: 5px;
            border: 1px ridge black;
            font-size: 0.8rem;
            height: auto;
            color: #8b8b8b;
        }

        button:hover {
            background-color: #65597c;
            color: white;
        }

        button:active {
            background-color: #201441;
            color: white;
        }
    </style>


</head>

<body>
    <div class="container">
        <div>
            <h2>Error 404, page not found</h2>
        </div>
        <div>
            <a href="/"><button>Return to main</button></a>
        </div>
</body>

</html>
)===";
