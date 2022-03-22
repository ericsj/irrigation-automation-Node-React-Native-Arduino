
const express = require('express');
const router = express.Router();
const irrigationMetricsRouter = require('./irrigation-metrics');

router.use('/irrigation-metrics', irrigationMetricsRouter);
module.exports = router;