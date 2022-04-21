<script>
export default {
    name: 'choice-page',
    methods: { 
        onClick : function(i) {
            this.$router.push('/word/:'+(i+4))
        }       
    },
}
</script>

<template>
<div>
    <h1>Bienvenue sur Wordchamp</h1>
    <button @click="onClick(i)" v-for="i in 5" :key="i">{{i+4}} lettres</button>
</div>
</template>

<style scoped>
</style>