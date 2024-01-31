String mainPageHtmlString(String URL) {

String HtmlString = R""(


<!DOCTYPE html>
<html lang="en" >
<head>
  <meta charset="UTF-8">
  <title>Contrl UI Screen</title>

  <link rel='stylesheet' href='https://cdn.staticfile.org/twitter-bootstrap/4.3.1/css/bootstrap.min.css'>
  <link rel='stylesheet' href='https://cdn.bootcss.com/font-awesome/5.13.0/css/all.css'>
  

<style>
/* @import url("https://fonts.googleapis.com/css2?family=Open+Sans&display=swap"); */

*,
*::before,
*::after {
  margin: 0;
  padding: 0;
  box-sizing: border-box;
}

:root {
  --background-color: #bbdefb;
  --blue-50: #e3f2fd;
  --blue-100: #bbdefb;
  --blue-A700: #2962ff;
  --green-50: #e8f5e9;
  --green-100: #c8e6c9;
  --green-A700: #00c853;
  --purple-50: #f3e5f5;
  --purple-100: #e1bee7;
  --purple-A700: #aa00ff;
  --orange-50: #fff3e0;
  --orange-100: #ffe0b2;
  --orange-A700: #ff6d00;
  --orange-700: #f57c00;
  --grey-900: #212121;
  --white: #ffffff;
  --round-button-active-color: #212121;
  --translate-main-slider: 100%;
  --main-slider-color: #e3f2fd;
  --translate-filters-slider: 0;
  --filters-container-height: 3.8rem;
  --filters-wrapper-opacity: 1;
}

html {
  font-size: 62.5%;
}

html,
body {
  height: 100%;
}

body {
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  transition: background-color 0.4s ease-in-out;
  background-color: var(--background-color);
}

button {
  border: none;
  cursor: pointer;
  background-color: transparent;
  outline: none;
}

nav.amazing-tabs {
  width: 80%;
  height: 30%;
  background-color: var(--white);
  border-radius: 2.5rem;
  user-select: none;
  padding-top: 1rem;
}

.main-tabs-container {
  padding: 0 1rem 1rem 1rem;
}

.main-tabs-wrapper {
  position: relative;
}

ul.main-tabs,
ul.filter-tabs {
  list-style-type: none;
  display: flex;
}

ul.main-tabs li {
  display: inline-flex;
  position: relative;
  padding: 1.5rem;
  z-index: 1;
}

.avatar,
.avatar img {
  height: 4rem;
  width: 4rem;
  border-radius: 50%;
  pointer-events: none;
}

.avatar img {
  object-fit: cover;
}

.round-button {
  height: 4.8rem;
  width: 4.8rem;
  border-radius: 50%;
  display: inline-flex;
  align-items: center;
  justify-content: center;
  color: var(--grey-900);
  transition: color 0.2s ease-in-out;
}

.round-button:hover,
.round-button.active {
  color: var(--round-button-active-color);
}

.round-button svg {
  pointer-events: none;
  height: 2.8rem;
  width: 2.8rem;
  transform: translate(0, 0);
}

.main-slider {
  pointer-events: none;
  position: absolute;
  top: 0;
  left: 0;
  padding: 1.5rem;
  z-index: 0;
  transition: transform 0.4s ease-in-out;
  transform: translateX(var(--translate-main-slider));
}

.main-slider-circle {
  height: 4.8rem;
  width: 4.8rem;
  border-radius: 50%;
  transition: background-color 0.4s ease-in-out;
  background-color: var(--main-slider-color);
}

.animate-jello {
  animation: jello-horizontal 0.9s both;
}

@keyframes jello-horizontal {
  0% {
    transform: scale3d(1, 1, 1);
  }
  30% {
    transform: scale3d(1.25, 0.75, 1);
  }
  40% {
    transform: scale3d(0.75, 1.25, 1);
  }
  50% {
    transform: scale3d(1.15, 0.85, 1);
  }
  65% {
    transform: scale3d(0.95, 1.05, 1);
  }
  75% {
    transform: scale3d(1.05, 0.95, 1);
  }
  100% {
    transform: scale3d(1, 1, 1);
  }
}

.filters-container {
  overflow: hidden;
  padding: 0 3rem;
  transition: max-height 0.4s ease-in-out;
  max-height: var(--filters-container-height);
}

.filters-wrapper {
  position: relative;
  transition: opacity 0.2s ease-in-out;
  opacity: var(--filters-wrapper-opacity);
}

.filter-tabs {
  border-radius: 1rem;
  padding: 0.3rem;
  overflow: hidden;
  background-color: var(--orange-50);
}

.filter-tabs li {
  position: relative;
  z-index: 1;
  display: flex;
  flex: 1 0 33.33%;
}

.filter-button {
  display: flex;
  align-items: center;
  justify-content: center;
  border-radius: 0.8rem;
  flex-grow: 1;
  height: 3rem;
  padding: 0 1.5rem;
  color: var(--orange-700);
  font-family: "Open Sans", sans-serif;
  font-weight: 400;
  font-size: 1.4rem;
}

.filter-button.filter-active {
  transition: color 0.4s ease-in-out;
  color: var(--grey-900);
}

.filter-slider {
  pointer-events: none;
  position: absolute;
  padding: 0.3rem;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  z-index: 0;
}

.filter-slider-rect {
  height: 3rem;
  width: 33.33%;
  border-radius: 0.8rem;
  background-color: var(--white);
  box-shadow: 0 0.1rem 1rem -0.4rem rgba(0, 0, 0, 0.12);
  transition: transform 0.4s ease-in-out;
  transform: translateX(var(--translate-filters-slider));
}  


.imagePreview {
    width: 100%;
    height: 180px;
    background-position: center center;
  background:url(http://cliquecities.com/assets/no-image-e3699ae23f866f6cbdf8ba2443ee5c4e.jpg);
  background-color:#fff;
    background-size: cover;
  background-repeat:no-repeat;
    display: inline-block;
  box-shadow:0px -3px 6px 2px rgba(0,0,0,0.2);
}
.btn-primary
{
  display:block;
  border-radius:0px;
  box-shadow:0px 4px 6px 2px rgba(0,0,0,0.2);
  margin-top:-5px;
}
.imgUp
{
  margin-bottom:15px;
}
.del
{
  position:absolute;
  top:0px;
  right:15px;
  width:30px;
  height:30px;
  text-align:center;
  line-height:30px;
  background-color:rgba(255,255,255,0.6);
  cursor:pointer;
}
.imgAdd
{
  width:30px;
  height:30px;
  border-radius:50%;
  background-color:#4bd7ef;
  color:#fff;
  box-shadow:0px 0px 2px 1px rgba(0,0,0,0.2);
  text-align:center;
  line-height:30px;
  margin-top:0px;
  cursor:pointer;
  font-size:15px;
}

/*image upload*/
.imagePreview {
    width: 100%;
    height: 180px;
    background-position: center center;
  background:url(http://cliquecities.com/assets/no-image-e3699ae23f866f6cbdf8ba2443ee5c4e.jpg);
  background-color:#fff;
    background-size: cover;
  background-repeat:no-repeat;
    display: inline-block;
  box-shadow:0px -3px 6px 2px rgba(0,0,0,0.2);
}
.btn-primary
{
  display:block;
  border-radius:0px;
  box-shadow:0px 4px 6px 2px rgba(0,0,0,0.2);
  margin-top:-5px;
}
.imgUp
{
  margin-bottom:15px;
}
.del
{
  position:absolute;
  top:0px;
  right:15px;
  width:30px;
  height:30px;
  text-align:center;
  line-height:30px;
  background-color:rgba(255,255,255,0.6);
  cursor:pointer;
}
.imgAdd
{
  width:30px;
  height:30px;
  border-radius:50%;
  background-color:#4bd7ef;
  color:#fff;
  box-shadow:0px 0px 2px 1px rgba(0,0,0,0.2);
  text-align:center;
  line-height:30px;
  margin-top:0px;
  cursor:pointer;
  font-size:15px;
}

/* input */
 
.inp {
  position: relative;
  margin: auto;
  left:15px;
  width: 100%;
  max-width: 280px;
  border-radius: 20px;
  overflow: hidden;
}
.inp .label {
  position: absolute;
  top: 10px;
  left: 12px;
  font-size: 16px;
  color: rgba(0, 0, 0, 0.5);
  font-weight: 500;
  transform-origin: 0 0;
  transform: translate3d(0, 0, 0);
  transition: all 0.2s ease;
  pointer-events: none;
}
.inp .focus-bg {
  position: absolute;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  background: rgba(0, 0, 0, 0.05);
  z-index: -1;
  transform: scaleX(0);
  transform-origin: left;
}
.inp input {
  -webkit-appearance: none;
  -moz-appearance: none;
       appearance: none;
  width: 100%;
  border: 0;
  font-family: inherit;
  padding: 16px 12px 0 12px;
  height: 56px;
  font-size: 16px;
  font-weight: 400;
  background: rgba(0, 0, 0, 0.02);
  box-shadow: inset 0 -1px 0 rgba(0, 0, 0, 0.3);
  color: #000;
  transition: all 0.15s ease;
}
.inp input:hover {
  background: rgba(0, 0, 0, 0.04);
  box-shadow: inset 0 -3px 0 rgba(0, 0, 0, 0.5);
}
.inp input:not(:-moz-placeholder-shown) + .label {
  color: rgba(0, 0, 0, 0.5);
  transform: translate3d(0, -12px, 0) scale(0.75);
}
.inp input:not(:-ms-input-placeholder) + .label {
  color: rgba(0, 0, 0, 0.5);
  transform: translate3d(0, -12px, 0) scale(0.75);
}
.inp input:not(:placeholder-shown) + .label {
  color: rgba(0, 0, 0, 0.5);
  transform: translate3d(0, -12px, 0) scale(0.75);
}
.inp input:focus {
  background: rgba(0, 0, 0, 0.05);
  outline: none;
  box-shadow: inset 0 -6px 0 #0077FF;
}
.inp input:focus + .label {
  color: #0077FF;
  transform: translate3d(0, -12px, 0) scale(0.75);
}
.inp input:focus + .label + .focus-bg {
  transform: scaleX(1);
  transition: all 0.1s ease;
}
</style>
</head>
<body>

<!-- partial:index.partial.html -->
<br><div class="container">
  <div class="row">
  <div class="col-sm-2 imgUp">
    <div class="imagePreview select"></div>
<label class="btn btn-primary">
                              Select<input type="file" class="uploadFile img" value="Upload Photo" style="width: 0px;height: 0px;overflow: hidden;">
        </label>
<!-- <label class="btn btn-primary">
                              Send<input type="file" class="uploadFile img" value="Upload Photo" style="width: 0px;height: 0px;overflow: hidden;">
</label> -->


  </div><!-- col-2 -->
  <i class="fa fa-plus imgAdd"></i>
 </div><!-- row -->
</div><!-- container -->
<!-- partial -->  
<!-- partial:index.partial.html -->




<nav class="amazing-tabs">
  <div class="filters-container">
    <div class="filters-wrapper">
      <ul class="filter-tabs">
        <li>
          <button class="filter-button filter-active" data-translate-value="0">
            New
          </button>
        </li>
        <li>
          <button class="filter-button" data-translate-value="100%">
            Popular
          </button>
        </li>
        <li>
          <button class="filter-button" data-translate-value="200%">
            Following
          </button>
        </li>
      </ul>
      <div class="filter-slider" aria-hidden="true">
        <div class="filter-slider-rect">&nbsp;</div>
      </div>
    </div>
  </div>
  <div class="main-tabs-container">
    <div class="main-tabs-wrapper">
      <ul class="main-tabs">
        <li>
          <button class="round-button page1" data-translate-value="0" data-color="red">
            <svg t="1705080920468" class="icon" viewBox="0 0 1024 1024" version="1.1" xmlns="http://www.w3.org/2000/svg" p-id="38396" width="200" height="200"><path d="M1024 212.992q0 70.656-46.08 121.856 46.08 89.088 46.08 193.536 0 96.256-39.936 181.248t-109.568 147.968-162.816 99.328-199.68 36.352-199.68-36.352-162.304-99.328-109.568-147.968-40.448-181.248q0-104.448 46.08-193.536-46.08-51.2-46.08-121.856 0-37.888 13.824-71.168t37.376-58.368 55.808-39.424 68.096-14.336q43.008 0 78.848 18.432t59.392 50.176q46.08-17.408 96.256-26.624t102.4-9.216 102.4 9.216 96.256 26.624q24.576-31.744 59.904-50.176t78.336-18.432q36.864 0 68.608 14.336t55.296 39.424 37.376 58.368 13.824 71.168zM205.824 627.712q10.24 0 18.944-10.24t15.36-28.672 10.24-42.496 3.584-51.712-3.584-51.712-10.24-41.984-15.36-28.16-18.944-10.24q-9.216 0-17.92 10.24t-15.36 28.16-10.752 41.984-4.096 51.712 4.096 51.712 10.752 42.496 15.36 28.672 17.92 10.24zM512 927.744q53.248 0 99.84-13.312t81.408-35.84 54.784-52.736 19.968-65.024q0-33.792-19.968-64t-54.784-52.736-81.408-35.84-99.84-13.312-99.84 13.312-81.408 35.84-54.784 52.736-19.968 64q0 34.816 19.968 65.024t54.784 52.736 81.408 35.84 99.84 13.312zM818.176 627.712q10.24 0 18.944-10.24t15.36-28.672 10.24-42.496 3.584-51.712-3.584-51.712-10.24-41.984-15.36-28.16-18.944-10.24q-9.216 0-17.92 10.24t-15.36 28.16-10.752 41.984-4.096 51.712 4.096 51.712 10.752 42.496 15.36 28.672 17.92 10.24zM512 660.48q39.936 0 68.096 9.728t28.16 24.064-28.16 24.064-68.096 9.728-68.096-9.728-28.16-24.064 28.16-24.064 68.096-9.728z" p-id="38397" fill="#2c2c2c"></path></svg>
          </button>
        </li>
        <li>
          <button class="round-button gallery active page2" style="--round-button-active-color: #2962ff" data-translate-value="100%" data-color="blue">
            <svg fill="currentColor" viewBox="0 0 16 16">
              <path d="M6.002 5.5a1.5 1.5 0 1 1-3 0 1.5 1.5 0 0 1 3 0z" />
              <path d="M2.002 1a2 2 0 0 0-2 2v10a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V3a2 2 0 0 0-2-2h-12zm12 1a1 1 0 0 1 1 1v6.5l-3.777-1.947a.5.5 0 0 0-.577.093l-3.71 3.71-2.66-1.772a.5.5 0 0 0-.63.062L1.002 12V3a1 1 0 0 1 1-1h12z" />
            </svg>
          </button>
        </li>
        <li>
          <button class="round-button page3" style="--round-button-active-color: #00c853" data-translate-value="200%" data-color="green">
            <svg t="1705080533413" class="icon" viewBox="0 0 1024 1024" version="1.1" xmlns="http://www.w3.org/2000/svg" p-id="30941" width="200" height="200"><path d="M910.222336 284.444672H113.77664V170.667008c0-31.419392 25.469952-56.889344 56.889344-56.889344h682.665984c31.419392 0 56.889344 25.469952 56.889344 56.889344v113.77664z m0 56.88832v512c0 31.419392-25.469952 56.889344-56.889344 56.889344H170.667008c-31.419392 0-56.889344-25.469952-56.889344-56.889344v-512H910.22336zM284.444672 170.667008l57.2416 113.77664h56.88832l-57.2416-113.77664h-56.88832z m170.665984 0l57.2416 113.77664H569.2416L512 170.668032h-56.889344z m170.667008 0l57.2416 113.77664h56.88832l-57.2416-113.77664h-56.88832z m6.00576 452.108288a28.444672 28.444672 0 0 0 12.721152-12.721152c7.02464-14.051328 1.330176-31.136768-12.721152-38.162432L439.38816 475.69408a28.444672 28.444672 0 0 0-12.720128-3.003392c-15.710208 0-28.444672 12.735488-28.444672 28.444672v192.396288c0 4.415488 1.028096 8.77056 3.002368 12.720128 7.025664 14.051328 24.112128 19.746816 38.162432 12.721152l192.396288-96.197632z" fill="#2c2c2c" p-id="30942"></path></svg>
          </button>
        </li>
        <li>
          <button class="round-button page4" style="--round-button-active-color: #aa00ff" data-translate-value="300%" data-color="purple">
            
              <svg t="1705080606551" class="icon" viewBox="0 0 1024 1024" version="1.1" xmlns="http://www.w3.org/2000/svg" p-id="33679" width="200" height="200"><path d="M512 56.889344c251.35104 0 455.110656 203.759616 455.110656 455.110656S763.35104 967.110656 512 967.110656 56.889344 763.35104 56.889344 512 260.64896 56.889344 512 56.889344z m30.036992 170.665984h-3.18464c-13.76768 0-24.576 10.467328-26.226688 23.665664-0.05632 0.683008-0.284672 1.195008-0.340992 1.878016-0.057344 0.454656-0.284672 0.852992-0.284672 1.307648v341.618688c-14.961664-7.964672-31.686656-12.914688-49.777664-12.914688h-71.11168c-58.88 0-106.665984 47.787008-106.665984 106.667008s47.785984 106.667008 106.665984 106.667008h71.11168c58.88 0 106.667008-47.787008 106.667008-106.667008 0-2.446336-0.569344-4.721664-0.740352-7.110656h0.740352V305.26464l76.34432 44.089344a28.326912 28.326912 0 0 0 14.164992 3.811328c9.842688 0 19.39968-5.12 24.633344-14.222336 7.907328-13.596672 3.243008-31.004672-10.353664-38.912l-116.451328-67.185664c-4.380672-3.072-9.387008-5.291008-15.190016-5.291008zM462.22336 640C489.643008 640 512 662.356992 512 689.777664s-22.356992 49.777664-49.777664 49.777664h-71.11168c-27.419648 0-49.77664-22.356992-49.77664-49.77664 0-27.421696 22.356992-49.778688 49.77664-49.778688h71.11168z" fill="#2c2c2c" p-id="33680"></path></svg>

          </button>
        </li>
        <li>
          <button class="round-button page5" style="--round-button-active-color: #ff6d00" data-translate-value="400%" data-color="orange">
            <svg t="1705080842606" class="icon" viewBox="0 0 1024 1024" version="1.1" xmlns="http://www.w3.org/2000/svg" p-id="37404" width="200" height="200"><path d="M853.333333 146.285714a73.142857 73.142857 0 0 1 73.142857 73.142857v487.619048a73.142857 73.142857 0 0 1-73.142857 73.142857H473.526857l-167.594667 109.836191A24.380952 24.380952 0 0 1 268.190476 869.61981V780.190476H170.666667a73.142857 73.142857 0 0 1-73.142857-73.142857V219.428571a73.142857 73.142857 0 0 1 73.142857-73.142857h682.666666zM543.207619 463.238095H341.333333v73.142857h201.874286v-73.142857zM682.666667 316.952381H341.333333v73.142857h341.333334v-73.142857z" p-id="37405" fill="#2c2c2c"></path></svg>
          </button>
            
        </li>
        <li>
          <button class="round-button page6" style="--round-button-active-color: #aa00ff" data-translate-value="500%" data-color="purple">
          <svg t="1705078821297" class="icon" viewBox="0 0 1024 1024" version="1.1" xmlns="http://www.w3.org/2000/svg" p-id="19595" width="200" height="200"><path d="M204.896 863.104a126.08 126.08 0 0 1-10.4-0.416C86.72 853.856 14.912 692.896 31.008 496.288 47.36 296.352 141.024 151.744 249.44 161.056c48.384 3.968 81.92 42.912 105.76 76.416a32 32 0 0 1-52.16 37.088c-23.456-32.96-41.6-48.288-58.816-49.728-59.008-4.256-135.584 107.584-149.408 276.672-13.824 169.056 44.192 292.384 104.928 297.344 52.96 4.96 105.024-61.152 132.192-166.848a31.968 31.968 0 0 1 30.976-24h299.904c14.432 0 27.072 9.664 30.88 23.552C722.848 738.24 774.912 803.904 829.024 798.4c29.408-2.976 57.28-33.632 76.448-84.096 22.208-58.592 30.016-135.04 21.888-215.232s-31.072-153.536-64.64-206.56c-28.928-45.696-62.016-70.592-91.744-67.2-18.336 1.888-39.616 19.2-59.808 48.736A31.968 31.968 0 0 1 684.736 288H448a32 32 0 0 1 0-64h220.48c29.28-37.92 61.568-58.848 96.064-62.336C871.872 150.72 971.136 296.256 991.04 492.672c9.088 89.888-0.032 176.672-25.76 244.384-28.512 75.072-74.592 119.456-129.824 125.056-81.76 8.352-156.128-63.968-196.544-190.08H387.104c-36.48 119.52-104.512 191.072-182.208 191.072zM320 448h-32v-32a32 32 0 0 0-64 0v32h-32a32 32 0 0 0 0 64h32v32a32 32 0 1 0 64 0v-32h32a32 32 0 0 0 0-64z m416-64a64 64 0 1 1 128 0 64 64 0 1 1-128 0zM608 512a64 64 0 1 1 128 0 64 64 0 1 1-128 0z" fill="#333333" p-id="19596"></path></svg>
          </button>
        </li>

      </ul>
      <div class="main-slider" aria-hidden="true">
        <div class="main-slider-circle">&nbsp;</div>
      </div>
     
    </div>
    <!-- input text -->
    <label for="inp" class="inp">
      <input type="text" id="inp" placeholder="&nbsp;"  onkeydown="handleKeyDown(event)">
      <span class="label">Type here ...</span>
      <span class="focus-bg"></span>
    </label>
  </div>
</nav>

<script>
  function handleKeyDown(event) {
      if (event.key === 'Enter') {
          // 获取输入框的值
          const inputValue = document.getElementById('inp').value;
          putJson(inputValue,"putinfo");
              
      }
  }
</script>



<!-- partial -->
<!-- <h1>Hello</h1> -->
<script >
    // resources in description
const mainTabs = document.querySelector(".main-tabs");
const mainSliderCircle = document.querySelector(".main-slider-circle");
const roundButtons = document.querySelectorAll(".round-button");

const colors = {
  blue: {
    50: {
      value: "#e3f2fd"
    },
    100: {
      value: "#bbdefb"
    }
  },
  green: {
    50: {
      value: "#e8f5e9"
    },
    100: {
      value: "#c8e6c9"
    }
  },
  purple: {
    50: {
      value: "#f3e5f5"
    },
    100: {
      value: "#e1bee7"
    }
  },
  orange: {
    50: {
      value: "#ffe0b2"
    },
    100: {
      value: "#ffe0b2"
    }
  },
  red: {
    50: {
      value: "#ffebee"
    },
    100: {
      value: "#ffcdd2"
    }
  },
  purple: {
    50: {
      value: "#f3e5f5"
    },
    100: {
      value: "#e1bee7"
    }
  }
};

const getColor = (color, variant) => {
  return colors[color][variant].value;
};

const handleActiveTab = (tabs, event, className) => {
  tabs.forEach((tab) => {
    tab.classList.remove(className);
  });

  if (!event.target.classList.contains(className)) {
    event.target.classList.add(className);
  }
};

mainTabs.addEventListener("click", (event) => {
  const root = document.documentElement;
  const targetColor = event.target.dataset.color;
  const targetTranslateValue = event.target.dataset.translateValue;

  if (event.target.classList.contains("round-button")) {
    mainSliderCircle.classList.remove("animate-jello");
    void mainSliderCircle.offsetWidth;
    mainSliderCircle.classList.add("animate-jello");

    root.style.setProperty("--translate-main-slider", targetTranslateValue);
    root.style.setProperty("--main-slider-color", getColor(targetColor, 50));
    root.style.setProperty("--background-color", getColor(targetColor, 100));

    handleActiveTab(roundButtons, event, "active");

    if (event.target.classList.contains("gallery")) {
      console.log("click");
      console.log(targetTranslateValue);
      root.style.setProperty("--filters-container-height", "3.8rem");
      root.style.setProperty("--filters-wrapper-opacity", "1");
      
      
    } else {
 
      root.style.setProperty("--filters-container-height", "0");
      root.style.setProperty("--filters-wrapper-opacity", "0");
    }

    if (event.target.classList.contains("page1")) {putJson("0","putPageIndex" )}
    if (event.target.classList.contains("page2")) {putJson("1","putPageIndex" )}
    if (event.target.classList.contains("page3")) {putJson("2","putPageIndex" )}
    if (event.target.classList.contains("page4")) {putJson("3","putPageIndex" )}
    if (event.target.classList.contains("page5")) {putJson("4","putPageIndex" )}
    if (event.target.classList.contains("page6")) {putJson("5","putPageIndex" )}


  }
});

const filterTabs = document.querySelector(".filter-tabs");
const filterButtons = document.querySelectorAll(".filter-button");

filterTabs.addEventListener("click", (event) => {
  const root = document.documentElement;
  const targetTranslateValue = event.target.dataset.translateValue;
  

  if (event.target.classList.contains("filter-button")) {
    root.style.setProperty("--translate-filters-slider", targetTranslateValue);
    handleActiveTab(filterButtons, event, "filter-active");
  }
});


function putJson(value,route){

  var url = "http://xxxxxxxxxx/"+route  //putPageIndex

  var request = new XMLHttpRequest();

  request.open("POST", url,true);


  //request.setRequestHeader("Content-Type", "application/json");

  var send_data  = {info:value} //"click_once_count"
  console.log(JSON.stringify(send_data));
  request.send(JSON.stringify(send_data)); 

  request.onload = function(e){
    console.log(" success");
    console.log(request.status, " status");
    console.log(request.readyState, "readyState");
    console.log(request.json);
    if (request.status === 200) {
      console.log(" success");

    }
    else{
      console.log(" fail");
    }
  }
  request.onerror = function(e){
  console.log(" fail");
  }
    

}


</script>


<script>
  //=============================================gif
  (function (root, factory) {
      if (typeof define === 'function' && define.amd) {
          define([], factory);
      } else if (typeof exports === 'object') {
          module.exports = factory();
      } else {
          root.SuperGif = factory();
      }
  }(this, function () {
      // Generic functions
      var bitsToNum = function (ba) {
          return ba.reduce(function (s, n) {
              return s * 2 + n;
          }, 0);
      };
  
      var byteToBitArr = function (bite) {
          var a = [];
          for (var i = 7; i >= 0; i--) {
              a.push( !! (bite & (1 << i)));
          }
          return a;
      };
  
      // Stream
      /**
       * @constructor
       */
      // Make compiler happy.
      var Stream = function (data) {
          this.data = data;
          this.len = this.data.length;
          this.pos = 0;
  
          this.readByte = function () {
              if (this.pos >= this.data.length) {
                  throw new Error('Attempted to read past end of stream.');
              }
              if (data instanceof Uint8Array)
                  return data[this.pos++];
              else
                  return data.charCodeAt(this.pos++) & 0xFF;
          };
  
          this.readBytes = function (n) {
              var bytes = [];
              for (var i = 0; i < n; i++) {
                  bytes.push(this.readByte());
              }
              return bytes;
          };
  
          this.read = function (n) {
              var s = '';
              for (var i = 0; i < n; i++) {
                  s += String.fromCharCode(this.readByte());
              }
              return s;
          };
  
          this.readUnsigned = function () { // Little-endian.
              var a = this.readBytes(2);
              return (a[1] << 8) + a[0];
          };
      };
  
      var lzwDecode = function (minCodeSize, data) {
          // TODO: Now that the GIF parser is a bit different, maybe this should get an array of bytes instead of a String?
          var pos = 0; // Maybe this streaming thing should be merged with the Stream?
          var readCode = function (size) {
              var code = 0;
              for (var i = 0; i < size; i++) {
                  if (data.charCodeAt(pos >> 3) & (1 << (pos & 7))) {
                      code |= 1 << i;
                  }
                  pos++;
              }
              return code;
          };
  
          var output = [];
  
          var clearCode = 1 << minCodeSize;
          var eoiCode = clearCode + 1;
  
          var codeSize = minCodeSize + 1;
  
          var dict = [];
  
          var clear = function () {
              dict = [];
              codeSize = minCodeSize + 1;
              for (var i = 0; i < clearCode; i++) {
                  dict[i] = [i];
              }
              dict[clearCode] = [];
              dict[eoiCode] = null;
  
          };
  
          var code;
          var last;
  
          while (true) {
              last = code;
              code = readCode(codeSize);
  
              if (code === clearCode) {
                  clear();
                  continue;
              }
              if (code === eoiCode) break;
  
              if (code < dict.length) {
                  if (last !== clearCode) {
                      dict.push(dict[last].concat(dict[code][0]));
                  }
              }
              else {
                  if (code !== dict.length) throw new Error('Invalid LZW code.');
                  dict.push(dict[last].concat(dict[last][0]));
              }
              output.push.apply(output, dict[code]);
  
              if (dict.length === (1 << codeSize) && codeSize < 12) {
                  // If we're at the last code and codeSize is 12, the next code will be a clearCode, and it'll be 12 bits long.
                  codeSize++;
              }
          }
  
          // I don't know if this is technically an error, but some GIFs do it.
          //if (Math.ceil(pos / 8) !== data.length) throw new Error('Extraneous LZW bytes.');
          return output;
      };
  
  
      // The actual parsing; returns an object with properties.
      var parseGIF = function (st, handler) {
          handler || (handler = {});
  
          // LZW (GIF-specific)
          var parseCT = function (entries) { // Each entry is 3 bytes, for RGB.
              var ct = [];
              for (var i = 0; i < entries; i++) {
                  ct.push(st.readBytes(3));
              }
              return ct;
          };
  
          var readSubBlocks = function () {
              var size, data;
              data = '';
              do {
                  size = st.readByte();
                  data += st.read(size);
              } while (size !== 0);
              return data;
          };
  
          var parseHeader = function () {
              var hdr = {};
              hdr.sig = st.read(3);
              hdr.ver = st.read(3);
              if (hdr.sig !== 'GIF') throw new Error('Not a GIF file.'); // XXX: This should probably be handled more nicely.
              hdr.width = st.readUnsigned();
              hdr.height = st.readUnsigned();
  
              var bits = byteToBitArr(st.readByte());
              hdr.gctFlag = bits.shift();
              hdr.colorRes = bitsToNum(bits.splice(0, 3));
              hdr.sorted = bits.shift();
              hdr.gctSize = bitsToNum(bits.splice(0, 3));
  
              hdr.bgColor = st.readByte();
              hdr.pixelAspectRatio = st.readByte(); // if not 0, aspectRatio = (pixelAspectRatio + 15) / 64
              if (hdr.gctFlag) {
                  hdr.gct = parseCT(1 << (hdr.gctSize + 1));
              }
              handler.hdr && handler.hdr(hdr);
          };
  
          var parseExt = function (block) {
              var parseGCExt = function (block) {
                  var blockSize = st.readByte(); // Always 4
                  var bits = byteToBitArr(st.readByte());
                  block.reserved = bits.splice(0, 3); // Reserved; should be 000.
                  block.disposalMethod = bitsToNum(bits.splice(0, 3));
                  block.userInput = bits.shift();
                  block.transparencyGiven = bits.shift();
  
                  block.delayTime = st.readUnsigned();
  
                  block.transparencyIndex = st.readByte();
  
                  block.terminator = st.readByte();
  
                  handler.gce && handler.gce(block);
              };
  
              var parseComExt = function (block) {
                  block.comment = readSubBlocks();
                  handler.com && handler.com(block);
              };
  
              var parsePTExt = function (block) {
                  // No one *ever* uses this. If you use it, deal with parsing it yourself.
                  var blockSize = st.readByte(); // Always 12
                  block.ptHeader = st.readBytes(12);
                  block.ptData = readSubBlocks();
                  handler.pte && handler.pte(block);
              };
  
              var parseAppExt = function (block) {
                  var parseNetscapeExt = function (block) {
                      var blockSize = st.readByte(); // Always 3
                      block.unknown = st.readByte(); // ??? Always 1? What is this?
                      block.iterations = st.readUnsigned();
                      block.terminator = st.readByte();
                      handler.app && handler.app.NETSCAPE && handler.app.NETSCAPE(block);
                  };
  
                  var parseUnknownAppExt = function (block) {
                      block.appData = readSubBlocks();
                      // FIXME: This won't work if a handler wants to match on any identifier.
                      handler.app && handler.app[block.identifier] && handler.app[block.identifier](block);
                  };
  
                  var blockSize = st.readByte(); // Always 11
                  block.identifier = st.read(8);
                  block.authCode = st.read(3);
                  switch (block.identifier) {
                      case 'NETSCAPE':
                          parseNetscapeExt(block);
                          break;
                      default:
                          parseUnknownAppExt(block);
                          break;
                  }
              };
  
              var parseUnknownExt = function (block) {
                  block.data = readSubBlocks();
                  handler.unknown && handler.unknown(block);
              };
  
              block.label = st.readByte();
              switch (block.label) {
                  case 0xF9:
                      block.extType = 'gce';
                      parseGCExt(block);
                      break;
                  case 0xFE:
                      block.extType = 'com';
                      parseComExt(block);
                      break;
                  case 0x01:
                      block.extType = 'pte';
                      parsePTExt(block);
                      break;
                  case 0xFF:
                      block.extType = 'app';
                      parseAppExt(block);
                      break;
                  default:
                      block.extType = 'unknown';
                      parseUnknownExt(block);
                      break;
              }
          };
  
          var parseImg = function (img) {
              var deinterlace = function (pixels, width) {
                  // Of course this defeats the purpose of interlacing. And it's *probably*
                  // the least efficient way it's ever been implemented. But nevertheless...
                  var newPixels = new Array(pixels.length);
                  var rows = pixels.length / width;
                  var cpRow = function (toRow, fromRow) {
                      var fromPixels = pixels.slice(fromRow * width, (fromRow + 1) * width);
                      newPixels.splice.apply(newPixels, [toRow * width, width].concat(fromPixels));
                  };
  
                  // See appendix E.
                  var offsets = [0, 4, 2, 1];
                  var steps = [8, 8, 4, 2];
  
                  var fromRow = 0;
                  for (var pass = 0; pass < 4; pass++) {
                      for (var toRow = offsets[pass]; toRow < rows; toRow += steps[pass]) {
                          cpRow(toRow, fromRow)
                          fromRow++;
                      }
                  }
  
                  return newPixels;
              };
  
              img.leftPos = st.readUnsigned();
              img.topPos = st.readUnsigned();
              img.width = st.readUnsigned();
              img.height = st.readUnsigned();
  
              var bits = byteToBitArr(st.readByte());
              img.lctFlag = bits.shift();
              img.interlaced = bits.shift();
              img.sorted = bits.shift();
              img.reserved = bits.splice(0, 2);
              img.lctSize = bitsToNum(bits.splice(0, 3));
  
              if (img.lctFlag) {
                  img.lct = parseCT(1 << (img.lctSize + 1));
              }
  
              img.lzwMinCodeSize = st.readByte();
  
              var lzwData = readSubBlocks();
  
              img.pixels = lzwDecode(img.lzwMinCodeSize, lzwData);
  
              if (img.interlaced) { // Move
                  img.pixels = deinterlace(img.pixels, img.width);
              }
  
              handler.img && handler.img(img);
          };
  
          var parseBlock = function () {
              var block = {};
              block.sentinel = st.readByte();
  
              switch (String.fromCharCode(block.sentinel)) { // For ease of matching
                  case '!':
                      block.type = 'ext';
                      parseExt(block);
                      break;
                  case ',':
                      block.type = 'img';
                      parseImg(block);
                      break;
                  case ';':
                      block.type = 'eof';
                      handler.eof && handler.eof(block);
                      break;
                  default:
                      throw new Error('Unknown block: 0x' + block.sentinel.toString(16)); // TODO: Pad this with a 0.
              }
  
              if (block.type !== 'eof') setTimeout(parseBlock, 0);
          };
  
          var parse = function () {
              parseHeader();
              setTimeout(parseBlock, 0);
          };
  
          parse();
      };
  
      var SuperGif = function ( opts ) {
          var options = {
              //viewport position
              vp_l: 0,
              vp_t: 0,
              vp_w: null,
              vp_h: null,
              //canvas sizes
              c_w: null,
              c_h: null
          };
          for (var i in opts ) { options[i] = opts[i] }
          if (options.vp_w && options.vp_h) options.is_vp = true;
  
          var stream;
          var hdr;
  
          var loadError = null;
          var loading = false;
  
          var transparency = null;
          var delay = null;
          var disposalMethod = null;
          var disposalRestoreFromIdx = null;
          var lastDisposalMethod = null;
          var frame = null;
          var lastImg = null;
  
          var playing = true;
          var forward = true;
  
          var ctx_scaled = false;
  
          var frames = [];
          var frameOffsets = []; // elements have .x and .y properties
  
          var gif = options.gif;
          if (typeof options.auto_play == 'undefined')
              options.auto_play = (!gif.getAttribute('rel:auto_play') || gif.getAttribute('rel:auto_play') == '1');
  
          var onEndListener = (options.hasOwnProperty('on_end') ? options.on_end : null);
          var loopDelay = (options.hasOwnProperty('loop_delay') ? options.loop_delay : 0);
          var overrideLoopMode = (options.hasOwnProperty('loop_mode') ? options.loop_mode : 'auto');
          var drawWhileLoading = (options.hasOwnProperty('draw_while_loading') ? options.draw_while_loading : true);
          var showProgressBar = drawWhileLoading ? (options.hasOwnProperty('show_progress_bar') ? options.show_progress_bar : true) : false;
          var progressBarHeight = (options.hasOwnProperty('progressbar_height') ? options.progressbar_height : 25);
          var progressBarBackgroundColor = (options.hasOwnProperty('progressbar_background_color') ? options.progressbar_background_color : 'rgba(255,255,255,0.4)');
          var progressBarForegroundColor = (options.hasOwnProperty('progressbar_foreground_color') ? options.progressbar_foreground_color : 'rgba(255,0,22,.8)');
  
          var clear = function () {
              transparency = null;
              delay = null;
              lastDisposalMethod = disposalMethod;
              disposalMethod = null;
              frame = null;
          };
  
          // XXX: There's probably a better way to handle catching exceptions when
          // callbacks are involved.
          var doParse = function () {
              try {
                  parseGIF(stream, handler);
              }
              catch (err) {
                  doLoadError('parse');
              }
          };
  
          var doText = function (text) {
              toolbar.innerHTML = text; // innerText? Escaping? Whatever.
              toolbar.style.visibility = 'visible';
          };
  
          var setSizes = function(w, h) {
              canvas.width = w * get_canvas_scale();
              canvas.height = h * get_canvas_scale();
              toolbar.style.minWidth = ( w * get_canvas_scale() ) + 'px';
  
              tmpCanvas.width = w;
              tmpCanvas.height = h;
              tmpCanvas.style.width = w + 'px';
              tmpCanvas.style.height = h + 'px';
              tmpCanvas.getContext('2d').setTransform(1, 0, 0, 1, 0, 0);
          };
  
          var setFrameOffset = function(frame, offset) {
              if (!frameOffsets[frame]) {
                  frameOffsets[frame] = offset;
                  return;
              }
              if (typeof offset.x !== 'undefined') {
                  frameOffsets[frame].x = offset.x;
              }
              if (typeof offset.y !== 'undefined') {
                  frameOffsets[frame].y = offset.y;
              }
          };
  
          var doShowProgress = function (pos, length, draw) {
              if (draw && showProgressBar) {
                  var height = progressBarHeight;
                  var left, mid, top, width;
                  if (options.is_vp) {
                      if (!ctx_scaled) {
                          top = (options.vp_t + options.vp_h - height);
                          height = height;
                          left = options.vp_l;
                          mid = left + (pos / length) * options.vp_w;
                          width = canvas.width;
                      } else {
                          top = (options.vp_t + options.vp_h - height) / get_canvas_scale();
                          height = height / get_canvas_scale();
                          left = (options.vp_l / get_canvas_scale() );
                          mid = left + (pos / length) * (options.vp_w / get_canvas_scale());
                          width = canvas.width / get_canvas_scale();
                      }
                      //some debugging, draw rect around viewport
                      if (false) {
                          if (!ctx_scaled) {
                              var l = options.vp_l, t = options.vp_t;
                              var w = options.vp_w, h = options.vp_h;
                          } else {
                              var l = options.vp_l/get_canvas_scale(), t = options.vp_t/get_canvas_scale();
                              var w = options.vp_w/get_canvas_scale(), h = options.vp_h/get_canvas_scale();
                          }
                          ctx.rect(l,t,w,h);
                          ctx.stroke();
                      }
                  }
                  else {
                      top = (canvas.height - height) / (ctx_scaled ? get_canvas_scale() : 1);
                      mid = ((pos / length) * canvas.width) / (ctx_scaled ? get_canvas_scale() : 1);
                      width = canvas.width / (ctx_scaled ? get_canvas_scale() : 1 );
                      height /= ctx_scaled ? get_canvas_scale() : 1;
                  }
  
                  ctx.fillStyle = progressBarBackgroundColor;
                  ctx.fillRect(mid, top, width - mid, height);
  
                  ctx.fillStyle = progressBarForegroundColor;
                  ctx.fillRect(0, top, mid, height);
              }
          };
  
          var doLoadError = function (originOfError) {
              var drawError = function () {
                  ctx.fillStyle = 'black';
                  ctx.fillRect(0, 0, options.c_w ? options.c_w : hdr.width, options.c_h ? options.c_h : hdr.height);
                  ctx.strokeStyle = 'red';
                  ctx.lineWidth = 3;
                  ctx.moveTo(0, 0);
                  ctx.lineTo(options.c_w ? options.c_w : hdr.width, options.c_h ? options.c_h : hdr.height);
                  ctx.moveTo(0, options.c_h ? options.c_h : hdr.height);
                  ctx.lineTo(options.c_w ? options.c_w : hdr.width, 0);
                  ctx.stroke();
              };
  
              loadError = originOfError;
              hdr = {
                  width: gif.width,
                  height: gif.height
              }; // Fake header.
              frames = [];
              drawError();
          };
  
          var doHdr = function (_hdr) {
              hdr = _hdr;
              setSizes(hdr.width, hdr.height)
          };
  
          var doGCE = function (gce) {
              pushFrame();
              clear();
              transparency = gce.transparencyGiven ? gce.transparencyIndex : null;
              delay = gce.delayTime;
              disposalMethod = gce.disposalMethod;
              // We don't have much to do with the rest of GCE.
          };
  
          var pushFrame = function () {
              if (!frame) return;
              frames.push({
                              data: frame.getImageData(0, 0, hdr.width, hdr.height),
                              delay: delay
                          });
              frameOffsets.push({ x: 0, y: 0 });
          };
  
          var doImg = function (img) {
              if (!frame) frame = tmpCanvas.getContext('2d');
  
              var currIdx = frames.length;
  
              //ct = color table, gct = global color table
              var ct = img.lctFlag ? img.lct : hdr.gct; // TODO: What if neither exists?
  
              /*
              Disposal method indicates the way in which the graphic is to
              be treated after being displayed.
  
              Values :    0 - No disposal specified. The decoder is
                              not required to take any action.
                          1 - Do not dispose. The graphic is to be left
                              in place.
                          2 - Restore to background color. The area used by the
                              graphic must be restored to the background color.
                          3 - Restore to previous. The decoder is required to
                              restore the area overwritten by the graphic with
                              what was there prior to rendering the graphic.
  
                              Importantly, "previous" means the frame state
                              after the last disposal of method 0, 1, or 2.
              */
              if (currIdx > 0) {
                  if (lastDisposalMethod === 3) {
                      // Restore to previous
                      // If we disposed every frame including first frame up to this point, then we have
                      // no composited frame to restore to. In this case, restore to background instead.
                      if (disposalRestoreFromIdx !== null) {
                        frame.putImageData(frames[disposalRestoreFromIdx].data, 0, 0);
                      } else {
                        frame.clearRect(lastImg.leftPos, lastImg.topPos, lastImg.width, lastImg.height);
                      }
                  } else {
                      disposalRestoreFromIdx = currIdx - 1;
                  }
  
                  if (lastDisposalMethod === 2) {
                      // Restore to background color
                      // Browser implementations historically restore to transparent; we do the same.
                      // http://www.wizards-toolkit.org/discourse-server/viewtopic.php?f=1&t=21172#p86079
                      frame.clearRect(lastImg.leftPos, lastImg.topPos, lastImg.width, lastImg.height);
                  }
              }
              // else, Undefined/Do not dispose.
              // frame contains final pixel data from the last frame; do nothing
  
              //Get existing pixels for img region after applying disposal method
              var imgData = frame.getImageData(img.leftPos, img.topPos, img.width, img.height);
  
              //apply color table colors
              img.pixels.forEach(function (pixel, i) {
                  // imgData.data === [R,G,B,A,R,G,B,A,...]
                  if (pixel !== transparency) {
                      imgData.data[i * 4 + 0] = ct[pixel][0];
                      imgData.data[i * 4 + 1] = ct[pixel][1];
                      imgData.data[i * 4 + 2] = ct[pixel][2];
                      imgData.data[i * 4 + 3] = 255; // Opaque.
                  }
              });
  
              frame.putImageData(imgData, img.leftPos, img.topPos);
  
              if (!ctx_scaled) {
                  ctx.scale(get_canvas_scale(),get_canvas_scale());
                  ctx_scaled = true;
              }
  
              // We could use the on-page canvas directly, except that we draw a progress
              // bar for each image chunk (not just the final image).
              if (drawWhileLoading) {
                  ctx.drawImage(tmpCanvas, 0, 0);
                  drawWhileLoading = options.auto_play;
              }
  
              lastImg = img;
          };
  
          var player = (function () {
              var i = -1;
              var iterationCount = 0;
  
              var showingInfo = false;
              var pinned = false;
  
              /**
               * Gets the index of the frame "up next".
               * @returns {number}
               */
              var getNextFrameNo = function () {
                  var delta = (forward ? 1 : -1);
                  return (i + delta + frames.length) % frames.length;
              };
  
              var stepFrame = function (amount) { // XXX: Name is confusing.
                  i = i + amount;
  
                  putFrame();
              };
  
              var step = (function () {
                  var stepping = false;
  
                  var completeLoop = function () {
                      if (onEndListener !== null)
                          onEndListener(gif);
                      iterationCount++;
  
                      if (overrideLoopMode !== false || iterationCount < 0) {
                          doStep();
                      } else {
                          stepping = false;
                          playing = false;
                      }
                  };
  
                  var doStep = function () {
                      stepping = playing;
                      if (!stepping) return;
  
                      stepFrame(1);
                      var delay = frames[i].delay * 10;
                      if (!delay) delay = 100; // FIXME: Should this even default at all? What should it be?
  
                      var nextFrameNo = getNextFrameNo();
                      if (nextFrameNo === 0) {
                          delay += loopDelay;
                          setTimeout(completeLoop, delay);
                      } else {
                          setTimeout(doStep, delay);
                      }
                  };
  
                  return function () {
                      if (!stepping) setTimeout(doStep, 0);
                  };
              }());
  
              var putFrame = function () {
                  var offset;
                  i = parseInt(i, 10);
  
                  if (i > frames.length - 1){
                      i = 0;
                  }
  
                  if (i < 0){
                      i = 0;
                  }
  
                  offset = frameOffsets[i];
  
                  tmpCanvas.getContext("2d").putImageData(frames[i].data, offset.x, offset.y);
                  ctx.globalCompositeOperation = "copy";
                  ctx.drawImage(tmpCanvas, 0, 0);
              };
  
              var play = function () {
                  playing = true;
                  step();
              };
  
              var pause = function () {
                  playing = false;
              };
  
  
              return {
                  init: function () {
                      if (loadError) return;
  
                      if ( ! (options.c_w && options.c_h) ) {
                          ctx.scale(get_canvas_scale(),get_canvas_scale());
                      }
  
                      if (options.auto_play) {
                          step();
                      }
                      else {
                          i = 0;
                          putFrame();
                      }
                  },
                  step: step,
                  play: play,
                  pause: pause,
                  playing: playing,
                  move_relative: stepFrame,
                  current_frame: function() { return i; },
                  length: function() { return frames.length },
                  move_to: function ( frame_idx ) {
                      i = frame_idx;
                      putFrame();
                  }
              }
          }());
  
          var doDecodeProgress = function (draw) {
              doShowProgress(stream.pos, stream.data.length, draw);
          };
  
          var doNothing = function () {};
          /**
           * @param{boolean=} draw Whether to draw progress bar or not; this is not idempotent because of translucency.
           *                       Note that this means that the text will be unsynchronized with the progress bar on non-frames;
           *                       but those are typically so small (GCE etc.) that it doesn't really matter. TODO: Do this properly.
           */
          var withProgress = function (fn, draw) {
              return function (block) {
                  fn(block);
                  doDecodeProgress(draw);
              };
          };
  
  
          var handler = {
              hdr: withProgress(doHdr),
              gce: withProgress(doGCE),
              com: withProgress(doNothing),
              // I guess that's all for now.
              app: {
                  // TODO: Is there much point in actually supporting iterations?
                  NETSCAPE: withProgress(doNothing)
              },
              img: withProgress(doImg, true),
              eof: function (block) {
                  //toolbar.style.display = '';
                  pushFrame();
                  doDecodeProgress(false);
                  if ( ! (options.c_w && options.c_h) ) {
                      canvas.width = hdr.width * get_canvas_scale();
                      canvas.height = hdr.height * get_canvas_scale();
                  }
                  player.init();
                  loading = false;
                  if (load_callback) {
                      load_callback(gif);
                  }
  
              }
          };
  
          var init = function () {
              var parent = gif.parentNode;
  
              var div = document.createElement('div');
              canvas = document.createElement('canvas');
              ctx = canvas.getContext('2d');
              toolbar = document.createElement('div');
  
              tmpCanvas = document.createElement('canvas');
  
              div.width = canvas.width = gif.width;
              div.height = canvas.height = gif.height;
              toolbar.style.minWidth = gif.width + 'px';
  
              div.className = 'jsgif';
              toolbar.className = 'jsgif_toolbar';
              div.appendChild(canvas);
              div.appendChild(toolbar);
  
              // parent.insertBefore(div, gif);
              // parent.removeChild(gif);
  
              if (options.c_w && options.c_h) setSizes(options.c_w, options.c_h);
              initialized=true;
          };
  
          var get_canvas_scale = function() {
              var scale;
              if (options.max_width && hdr && hdr.width > options.max_width) {
                  scale = options.max_width / hdr.width;
              }
              else {
                  scale = 1;
              }
              return scale;
          }
  
          var canvas, ctx, toolbar, tmpCanvas;
          var initialized = false;
          var load_callback = false;
  
          var load_setup = function(callback) {
              if (loading) return false;
              if (callback) load_callback = callback;
              else load_callback = false;
  
              loading = true;
              frames = [];
              clear();
              disposalRestoreFromIdx = null;
              lastDisposalMethod = null;
              frame = null;
              lastImg = null;
  
              return true;
          }
  
          return {
              // play controls
              play: player.play,
              pause: player.pause,
              move_relative: player.move_relative,
              move_to: player.move_to,
  
              // getters for instance vars
              get_playing      : function() { return playing },
              get_canvas       : function() { return canvas },
              get_canvas_scale : function() { return get_canvas_scale() },
              get_loading      : function() { return loading },
              get_auto_play    : function() { return options.auto_play },
              get_length       : function() { return player.length() },
              get_current_frame: function() { return player.current_frame() },
              load_url: function(src,callback){
                  if (!load_setup(callback)) return;
  
                  var h = new XMLHttpRequest();
                  // new browsers (XMLHttpRequest2-compliant)
                  h.open('GET', src, true);
                  
                  if ('overrideMimeType' in h) {
                      h.overrideMimeType('text/plain; charset=x-user-defined');
                  }
  
                  // old browsers (XMLHttpRequest-compliant)
                  else if ('responseType' in h) {
                      h.responseType = 'arraybuffer';
                  }
  
                  // IE9 (Microsoft.XMLHTTP-compliant)
                  else {
                      h.setRequestHeader('Accept-Charset', 'x-user-defined');
                  }
  
                  h.onloadstart = function() {
                      // Wait until connection is opened to replace the gif element with a canvas to avoid a blank img
                      if (!initialized) init();
                  };
                  h.onload = function(e) {
                      if (this.status != 200) {
                          doLoadError('xhr - response');
                      }
                      // emulating response field for IE9
                      if (!('response' in this)) {
                          this.response = new VBArray(this.responseText).toArray().map(String.fromCharCode).join('');
                      }
                      var data = this.response;
                      if (data.toString().indexOf("ArrayBuffer") > 0) {
                          data = new Uint8Array(data);
                      }
  
                      stream = new Stream(data);
                      setTimeout(doParse, 0);
                  };
                  h.onprogress = function (e) {
                      if (e.lengthComputable) doShowProgress(e.loaded, e.total, true);
                  };
                  h.onerror = function() { doLoadError('xhr'); };
                  h.send();
              },
              load: function (callback) {
                
                  this.load_url(  gif.src ||gif.getAttribute('rel:animated_src'),callback);
              },
              load_raw: function(arr, callback) {
                  if (!load_setup(callback)) return;
                  if (!initialized) init();
                  stream = new Stream(arr);
                  setTimeout(doParse, 0);
              },
              set_frame_offset: setFrameOffset
          };
      };
  
      return SuperGif;
  }));
  //=============================================
    </script>




<script src='http://cdnjs.cloudflare.com/ajax/libs/jquery/2.0.0/jquery.min.js'></script>
<script src='https://cdnjs.cloudflare.com/ajax/libs/jqueryui/1.12.1/jquery-ui.min.js'></script>
<script src='https://cdn.staticfile.org/twitter-bootstrap/4.3.1/js/bootstrap.min.js'></script>
<script >
  $(".imgAdd").click(function(){
  $(this).closest(".row").find('.imgAdd').before('<div class="col-sm-2 imgUp"><div class="imagePreview select"></div><label class="btn btn-primary">Upload<input type="file" class="uploadFile img" value="Upload Photo" style="width:0px;height:0px;overflow:hidden;"></label><i class="fa fa-times del"></i></div>');
});
$(document).on("click", "i.del" , function() {
//  to remove card
  $(this).parent().remove();
// to clear image
  // $(this).parent().find('.imagePreview').css("background-image","url('')");
});
$(document).on("click", ".select" , function() {
//  to remove card
  
// console.log(this.className);
// console.log(this.closest('.imgUp').className);
// console.log(this.closest('.imgUp').querySelector('.btn').querySelector('.uploadFile').className);
var fileInput = this.closest('.imgUp').querySelector('.btn').querySelector('.uploadFile');


  // var files = !!this.files ? this.files : [];
  var file = fileInput.files[0];
  postPIC(file);
// to clear image
  // $(this).parent().find('.imagePreview').css("background-image","url('')");
});
$(function() {
    $(document).on("change",".uploadFile", function()
    {
        var uploadFile = $(this);
        var files = !!this.files ? this.files : [];
        if (!files.length || !window.FileReader) return; // no file selected, or no FileReader support
 
        if (/^image/.test( files[0].type)){ // only image file
            var reader = new FileReader(); // instance of the FileReader
//
            const file = files[0];
            postPIC(file);
//
            reader.readAsDataURL(files[0]); // read the local file
            reader.onloadend = function(){ // set image data as background of div
                //alert(uploadFile.closest(".upimage").find('.imagePreview').length);
            uploadFile.closest(".imgUp").find('.imagePreview').css("background-image", "url("+this.result+")");
            }
        }
      
    });
});



function get_pic_base64(img,img_quality){
  const canvas = document.createElement('canvas');
  const ctx = canvas.getContext('2d');
  // Resize image to 240x240
  canvas.width = 240;
  canvas.height = 240;
  ctx.drawImage(img, 0, 0, 240, 240);

  // Convert to base64
  const resizedBase64 = canvas.toDataURL('image/jpeg',img_quality);

  var imageData = resizedBase64.split(',')[1]; // 获取图像数据
  return imageData;
}


function post_pic(imageData,index,url){ //'http://192.168.43.216/upload_image'

  var xhr = new XMLHttpRequest();
  xhr.open('POST',url , true); // 替换为ESP32的IP地址和端口
  var formData = new FormData();   
  formData.append('image', imageData); // 将图像数据添加到FormData对象
  formData.append('frame_index', index); // 将图像数据添加到FormData对象
  // formData.append('image1', "0"); // 将图像数据添加到FormData对象
  // formData.append('image2', "0"); // 将图像数据添加到FormData对象
  xhr.send(formData);

  xhr.onreadystatechange = function() {
  if (xhr.readyState === 4 && xhr.status === 200) {
      console.log('Image uploaded successfully.');
  }
  };  
}


function post_gif(img,url){
 // if (file && file.type === 'image/gif') {
    // var arrayBuffer = img.src;

    load_gif();
    var gifImgLen , gifImgList = [];
    function load_gif() {
      // 新建gif实例
      var rub = new SuperGif({
        gif:img, //必需：img 标签的 DOM 元素
        loop_mode:true, //可选：将此设置为 false 将强制禁用 gif 循环。
        auto_play:1, //可选：与上面的img标签 rel:auto_play 属性相同，这个 arg 覆盖了 img 标签信息。
        max_width:240, //可选：将 max_width 上的图像缩小到 max_width。对手机端访问有帮助。
        rubbable:1, //可选：让它可以擦掉。
        // on_end:()=>{console.log('gif 到达单个循环（一次迭代）结束')}, //可选：添加当 gif 到达单个循环（一次迭代）结束时的回调。传递的第一个参数是 gif HTMLElement。
        loop_delay:0, //可选：每次循环（迭代）后暂停的时间（以毫秒为单位）。
        progressbar_height:10, //可选：进度条的高度。
        progressbar_background_color:'#00ff00', //可选：进度条的背景颜色。
        progressbar_foreground_color:'#0000ff', //可选：进度条的前景色。
      });
      rub.load(function() {
        // console.log(rub);
        gifImgLen = rub.get_length();
        // console.log(gifImgLen);
        
        for (var i = 0; i < gifImgLen; i++) {
          // console.log(i);
          // 遍历gif实例的每一帧
          rub.move_to(i);
    
          // var img = new Image();
          // img.src =rub.get_canvas().toDataURL('image/jpeg'); 

          // const canvas_tmp = document.createElement('canvas');
          // const ctx_tmp = canvas_tmp.getContext('2d');    
          // canvas_tmp.width = 240;
          // canvas_tmp.height = 240;
          // ctx_tmp.drawImage(img, 0, 0, 240, 240);

          const resizedBase64 =rub.get_canvas().toDataURL('image/jpeg',0.2).split(',')[1];
          console.log(resizedBase64.length);
          post_pic(resizedBase64,i.toString(),url);
          if (i>8) break;

        }
        
      })
    }



    return gifImgList;
  //}
}


function postPIC(file){


  if (file) {
    const reader = new FileReader();

    reader.onload = function (e) {
        const img = new Image();
        img.src = e.target.result;
        console.log();

        if (file && file.type === 'image/gif'){
          url = "http://xxxxxxxxxx/upload_gif"
          console.log("gif");
          post_gif(img,url);


        }
        else{
        img.onload = function () {
            var imageData = get_pic_base64(img,0.8,file);
            var imageData_length = imageData.length;
            console.log(imageData_length);
            url = 'http://xxxxxxxxxx/upload_image';
            if (imageData_length<=1500){
              
              post_pic(imageData,"0",url);
            }
            else{
              imageData = get_pic_base64(img,0.7,file);
              post_pic(imageData,"0",url);
            }
            console.log(e.target.result);
        };
      };

    };

    reader.readAsDataURL(file);
    } else {
        alert('Please select an image');
    }

}

</script>



</body>
</html>


  )"";

String replace_String = "xxxxxxxxxx";
HtmlString. replace(replace_String,URL);
return HtmlString;
}
