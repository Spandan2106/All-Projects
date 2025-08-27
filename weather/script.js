// script.js
const API_KEY = "aa56c2c3f5513c6726400df387b662d3"; // Replace with your actual OpenWeatherMap API key

document.getElementById("getWeather").addEventListener("click", () => {
  const city = document.getElementById("city").value;
  if (!city) {
    alert("Please enter a city name");
    return;
  }
  getWeather(city);
});

async function getWeather(city) {
  try {
    const response = await fetch(
      `https://api.openweathermap.org/data/2.5/weather?q=${city}&appid=${API_KEY}&units=metric`
    );
    const data = await response.json();

    if (data.cod === "404") {
      document.getElementById("result").innerHTML = "<p>City not found!</p>";
      return;
    }

    document.getElementById("result").innerHTML = `
      <h2>${data.name}, ${data.sys.country}</h2>
      <p>🌡 Temperature: ${data.main.temp}°C</p>
      <p>🌥 Weather: ${data.weather[0].description}</p>
    `;
  } catch (error) {
    console.error("Error fetching weather data:", error);
    document.getElementById("result").innerHTML = "<p>Something went wrong!</p>";
  }
}
