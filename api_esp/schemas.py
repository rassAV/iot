from fastapi import APIRouter
from pydantic import BaseModel
from datetime import datetime

class TemperatureValue(BaseModel):
    value: float
    location: str
    device_id: str

class TemperatureValueWithTimestamp(BaseModel):
    value: float
    location: str
    device_id: str
    timestamp: datetime

router = APIRouter()