const express = require('express');
const app = express();

// --- Middleware ---
// Serve static files (like dashboard.html) from the 'public' folder
app.use(express.static('public'));
// Allow the server to understand JSON data in request bodies
app.use(express.json());


// --- API Routes ---
// Each feature from your C++ core gets its own route file
app.use('/api/flights', require('./routes/flights'));
app.use('/api/baggage', require('./routes/baggage'));
app.use('/api/lost-baggage', require('./routes/lost'));
app.use('/api/delays', require('./routes/delays'));
app.use('/api/gates', require('./routes/gates'));
app.use('/api/dashboard', require('./routes/dashboard'));


// --- Start the Server ---
const PORT = process.env.PORT || 5000;
app.listen(PORT, () => console.log(`🚀 Server started on port ${PORT}`));