<template v-slot:thumb-label='{value}'>
    <v-slider
            v-model="slider"
            :thumb-size=thumbSize
            :thumb-label=thumbLabel
            step=1
            ticks='true'
            :max=max
            :min=min
            :messages=message
            color=color
        >
    </v-slider>
</template>

<script>
export default {
    props:{
        max: Number,
        min: Number,
        message: String,
        thumbLabel: String,
        thumbSize: String,
        color: String,
    },
    data() {
        return {
            slider: 0,
            value: 0,
        }
    }
}
</script>