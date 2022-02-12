
const express = require('express');
const router = express.Router();
const irrigationMetricsRouter = require('./irrigation-metrics');
const systemStatusRouter = require('./system-status');

router.use('/irrigation-metrics', irrigationMetricsRouter);
router.use('/system-status', systemStatusRouter);
module.exports = router;