const char *HTML_HOME_PAGE = R"(
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
        }

        .file_upload_form {
            background: #3f3f3f;
            margin: 0 auto;
            padding: 20px;
            border: 1px solid black;
            width: auto;

            display: flex;
            justify-content: space-between;
            flex-direction: column;
            align-items: center;
        }

        .file_upload_form ol {
            padding-left: 0;
        }

        .preview {
            margin-top: 15px;
        }

        .file_upload_form li,
        .preview>p {
            background: #575757;
            display: flex;
            justify-content: space-between;
            margin-bottom: 10px;
            list-style-type: none;
            border: 1px solid black;
        }

        .file_upload_form img {
            height: 64px;
            order: 1;
        }

        .file_upload_form p {
            line-height: 32px;
            padding-left: 10px;
        }

        .file_upload_form label,
        button {
            background-color: #372a54;
            padding: 5px 10px;
            border-radius: 5px;
            border: 1px ridge black;
            font-size: 0.8rem;
            height: auto;
            color: #8b8b8b;
        }

        .file_upload_form label:hover,
        button:hover {
            background-color: #65597c;
            color: white;
        }

        .file_upload_form label:active,
        button:active {
            background-color: #201441;
            color: white;
        }

        .dirs-container {
            display: flex;
            flex-direction: column;
            justify-content: space-between;
            align-items: center;
        }

        .directories {
            min-width: 70%;
        }

        .directories>li {
            display: flex;
            flex-direction: row;
            justify-content: space-between;
            align-items: center;
            border-radius: 5px;
            background: #717171;
            margin: 10px auto;
        }

        .directories>li>div {
            text-align: center;
        }

        .directories>li>div>* {
            margin: 5px auto;
        }

        .dir_header {
            background: #575757 !important;
        }

        .file_name {
            flex: 2;
        }

        .file_size {
            flex: 2;
        }

        .download_wrapper {
            flex: 1;
        }

        .delete_wrapper {
            flex: 1;
        }

        .space_left {
            flex: 2;
        }
    </style>


</head>

<body>
    <div class="container">
        <form class="file_upload_form" method="post" action="/upload" enctype="multipart/form-data">
            <div>
                <label for="file_upload">Choose file to upload to ESP32</label>
                <input type="file" id="file_upload" name="file_upload">
            </div>
            <div class="preview">
                <p>No file currently selected for upload</p>
            </div>
            <div>
                <button class="file_submit_btn">Upload</button>
            </div>
        </form>


        <div class="dirs-container">
            <ul class="directories">

                <li class="dir_header">
                    <div class="file_name">
                        <p>File name</p>
                    </div>
                    <div class="file_size">
                        <p>Size</p>
                    </div>
                    <div class="space_left">Used: 2574Mb / 30424Mb</div>
                </li>

                <li>
                    <div class="file_name">
                        <p>README.md</p>
                    </div>
                    <div class="file_size">
                        <p>245 b</p>
                    </div>
                    <div class="download_wrapper"><button class="download_btn">Download</button></div>
                    <div class="delete_wrapper"><button class="delete_btn">Delete</button></div>
                </li>

                <li>
                    <div class="file_name">
                        <p>.gitignore</p>
                    </div>
                    <div class="file_size">
                        <p>141 Kb</p>
                    </div>
                    <div class="download_wrapper"><button class="download_btn">Download</button></div>
                    <div class="delete_wrapper"><button class="delete_btn">Delete</button></div>
                </li>

                <li>
                    <div class="file_name">
                        <p>image.jpg</p>
                    </div>
                    <div class="file_size">
                        <p>831 Kb</p>
                    </div>
                    <div class="download_wrapper"><button class="download_btn">Download</button></div>
                    <div class="delete_wrapper"><button class="delete_btn">Delete</button></div>
                </li>

                <li>
                    <div class="file_name">
                        <p>movie.mp4</p>
                    </div>
                    <div class="file_size">
                        <p>98 Mb</p>
                    </div>
                    <div class="download_wrapper"><button class="download_btn">Download</button></div>
                    <div class="delete_wrapper"><button class="delete_btn">Delete</button></div>
                </li>

            </ul>
        </div>
    </div>


    <script>
        const input = document.querySelector("#file_upload");
        const preview = document.querySelector(".preview");

        input.style.opacity = 0;
        input.style.width = 0;

        input.addEventListener("change", updateImageDisplay);

        function updateImageDisplay() {
            while (preview.firstChild) {
                preview.removeChild(preview.firstChild);
            }

            const curFiles = input.files;
            if (curFiles.length === 0) {
                const para = document.createElement("p");
                para.textContent = "No file currently selected for upload";
                preview.appendChild(para);
            } else {
                const list = document.createElement("ol");
                preview.appendChild(list);

                for (const file of curFiles) {
                    const listItem = document.createElement("li");
                    const para = document.createElement("p");
                    para.textContent = `File name ${file.name}, file size ${returnFileSize(
                        file.size,
                    )}.`;
                    const image = document.createElement("img");
                    image.src = URL.createObjectURL(file);
                    image.alt = image.title = file.name;

                    listItem.appendChild(image);
                    listItem.appendChild(para);

                    list.appendChild(listItem);
                }
            }
        }

        function returnFileSize(number) {
            if (number < 1024) {
                return `${number} bytes`;
            } else if (number >= 1024 && number < 1048576) {
                return `${(number / 1024).toFixed(1)} KB`;
            } else if (number >= 1048576) {
                return `${(number / 1048576).toFixed(1)} MB`;
            }
        }

        const upload_button = document.querySelector(".file_submit_btn");
        upload_button.addEventListener("click", (e) => {
            const file_input = document.querySelector("#file_upload");
            const file = file_input.files[0]
            const formData = new FormData();
            formData.append(file.name, file);

            console.log(file.name);
            fetch('/upload', {
                method: 'POST',
                body: formData
            })
                .then((rsp) => rsp.json())
                .then((obj) => {
                    console.log(obj);
                });
             event.preventDefault();
        });

        function get_file_data(btn) {
            const parent = (btn.parentElement).parentElement;
            const name = parent.querySelector(".file_name>p").innerHTML;
            const size = parent.querySelector(".file_size>p").innerHTML;
            return [name, size];
        }

        const download_btns = document.querySelectorAll(".download_btn");
        download_btns.forEach((download_btn) => {

            download_btn.addEventListener("click", (e) => {
                console.log("Download button pressed");

                const [file_name, file_size] = get_file_data(download_btn);
                console.log(file_name);
                console.log(file_size);

            });

        });

        const delete_btns = document.querySelectorAll(".delete_btn");
        delete_btns.forEach((delete_btn) => {

            delete_btn.addEventListener("click", (e) => {
                var confirmation = confirm("Are you sure you want to delete %FILE_NAME%?");
                if (confirmation) {
                    console.log("File delete approved");

                    const [file_name, file_size] = get_file_data(delete_btn);
                    console.log(file_name);
                    console.log(file_size);

                } else {
                    console.log("File delete canceled");
                }
            });

        })

    </script>
</body>

</html>
)";
