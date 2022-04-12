<script setup>
import Letter from '@/components/Letter.vue';
import {defineProps} from "vue"

// la méthode de construire en fonction de la taille de la solution me semble vraiment pas opti cela induit une sorte de ralentissement chiant
const rowprop = defineProps({
    solution: String,
    word: String,
    submitted: Boolean,
})


const a = new Array(rowprop.solution.length);
a[0] = "grey"


</script>

<template>
<b-container>
<b-row class="justify-content-md-center" style="font-size:50px;">
    <letter v-for="i in rowprop.solution.length" :key="i" :letter=word[i-1]></letter>
</b-row>
</b-container>


</template>


<style scoped>

</style>