<template>
<div class="col border border-dark" style="max-width:100px; max-height:100px; align-content:center">
    <p>P</p>
</div>



</template>


<script setup>
import {defineProps} from "vue"

const letterprop = defineProps({
    letter: {
        type: String,
        default: "",
    },
})

console.log(letterprop);

</script>



<style scoped>

</style>