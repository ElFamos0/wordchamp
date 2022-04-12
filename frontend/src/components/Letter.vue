<template>
<b-col class="border" style="max-width:75px; height:75px; background:#1e1e1e; color:#ffffff">
    {{letter}}
</b-col>
</template>


<script setup>
import {defineProps} from "vue"


const letterprop = defineProps({
    letter: {
        type: String,
        default: "",
    },
})

console.log(letterprop.letter); // to avoid unused variable warning

</script>
