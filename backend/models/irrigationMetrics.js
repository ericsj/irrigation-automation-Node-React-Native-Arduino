const irrigationMetrics = (sequelize, DataTypes) => {
  const IrrigationMetrics = sequelize.define('IrrigationMetrics', {
    id: {
      type: DataTypes.INTEGER,
      autoIncrement: true,
      allowNull: false,
      primaryKey: true
    },
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
