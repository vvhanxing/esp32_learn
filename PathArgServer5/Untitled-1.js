const axios = require('axios');
const fs = require('fs');
const path = require('path');
const { promisify } = require('util');
const { createCanvas, loadImage } = require('canvas');

const picFileName = 'a2.jpg';

// Read the image file
const readFile = promisify(fs.readFile);
readFile(path.resolve(__dirname, picFileName))
  .then(async (data) => {
    // Convert image data to base64
    const imgStr = Buffer.from(data).toString('base64');

    // Construct POST request data
    const postData = {
      image: imgStr,
    };

    // Set ESP32 IP address
    const esp32IP = 'http://192.168.43.153';
    const uploadEndpoint = '/upload_image';
    const url = `${esp32IP}${uploadEndpoint}`;

    // Send POST request using axios
    try {
      const response = await axios.post(url, postData);
      // Output ESP32 response information
      console.log(response.data);
    } catch (error) {
      console.error('Error:', error.message);
    }
  })
  .catch((error) => {
    console.error('Error reading the image file:', error.message);
  });
