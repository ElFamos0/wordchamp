<template>
<b-container>
<div class="row justify-content-md-center">
    <letter v-for="i in 8" :key="i"></letter>
    
</div>
</b-container>


</template>


<script setup>
import Letter from '@/components/Letter.vue';
import {defineProps} from "vue"

const rowprop = defineProps({
    solution: Boolean,
    word: String,
    submitted: Boolean,
})

console.log(rowprop);

</script>



<style scoped>

</style>