const irrigationMetrics = (sequelize, DataTypes) => {
  const IrrigationMetrics = sequelize.define('IrrigationMetrics', {
    duration: {
      type: DataTypes.INTEGER
    },
    initialMoisture: {
      type: DataTypes.INTEGER
    },
    finalMoisture: {
      type: DataTypes.INTEGER
    }
  })
  return IrrigationMetrics
}

module.exports = irrigationMetrics
